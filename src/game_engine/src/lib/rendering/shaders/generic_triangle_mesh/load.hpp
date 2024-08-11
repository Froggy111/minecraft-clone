#pragma once

// GL
#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/defines/config.hpp"
#include "game_engine/src/lib/rendering/shaders/shaders.hpp"

// EXTERNAL LIBS
#include <string>
#include <vector>
#include <functional>

#define GENERIC_TRIANGLE_MESH_VERT_SHADER_PATH "game_engine/src/game_engine/src/lib/rendering/shaders/generic_triangle_mesh/main_vert.vert"
#define GENERIC_TRIANGLE_MESH_MODEL_TRANSFORM_NAME "model_transform"
#define GENERIC_TRIANGLE_MESH_PERSPECTIVE_TRANSFORM_NAME "perspective_transform"

#define GENERIC_TRIANGLE_MESH_FRAG_SHADER_PATH "game_engine/src/game_engine/src/lib/rendering/shaders/generic_triangle_mesh/main_frag.frag"

namespace shaders {
  class GenericTriangleMeshShader {
  public:
    GenericTriangleMeshShader(std::vector<std::string> const &vert_shader_paths = {GENERIC_TRIANGLE_MESH_VERT_SHADER_PATH},
                              std::vector<std::string> const &frag_shader_paths = {GENERIC_TRIANGLE_MESH_FRAG_SHADER_PATH}):
      shader(vert_shader_paths, frag_shader_paths)
    {
      uniform_model_transform = glGetUniformLocation(shader.program_id(), GENERIC_TRIANGLE_MESH_MODEL_TRANSFORM_NAME);
      uniform_perspective_transform = glGetUniformLocation(shader.program_id(), GENERIC_TRIANGLE_MESH_PERSPECTIVE_TRANSFORM_NAME);
      return;
    }

    inline void set_uniform_model_transform(glm::mat4 const &model_transform) {
      glUniformMatrix4fv(this->uniform_model_transform, 1, GL_FALSE, glm::value_ptr(model_transform));
      return;
    }

    inline void set_uniform_perspective_transform(glm::mat4 const &perspective_transform) {
      glUniformMatrix4fv(this->uniform_perspective_transform, 1, GL_FALSE, glm::value_ptr(perspective_transform));
      return;
    }
 
    inline void use(void) {
      this->shader.use();
      return;
    }
    inline u32 vert_shader_ids(void) {
      return this->shader.vert_shader_ids();
    }
    inline u32 frag_shader_ids(void) {
      return this->shader.frag_shader_ids();
    }
    inline u32 program_id(void) {
      return this->shader.program_id();
    }
  private:
    rendering::Shader shader;
    u32 uniform_model_transform;
    u32 uniform_perspective_transform;
  };
}
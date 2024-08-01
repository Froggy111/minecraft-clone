#pragma once

// GL
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

// LIBS
#include "lib/defines/typedefs.hpp"

// EXTERN LIBS
#include <string>
#include <vector>
#include <functional>

namespace rendering {
  enum ShaderType {
    vert_frag_shader,
    vert_geom_frag_shader,
    comp_shader
  };

  /**
   * @class
   * @brief Generic shader class.
   * Wrapper for generic OpenGL shader programs.
   * Supports vert->frag, vert->geom->frag, and compute shaders.
   * Uniforms need to be additionally implemented by wrapping the shader class.
   */
  class Shader {
  public:
    Shader(std::vector<std::string> vert_shader_paths, std::vector<std::string> frag_shader_paths);
    Shader(std::vector<std::string> vert_shader_paths, std::vector<std::string> geom_shader_paths, std::vector<std::string> frag_shader_paths);
    Shader(std::vector<std::string> comp_shader_paths);
    void use(void);
    inline std::vector<u32> vert_shader_ids(void) {
      return this->_vert_shader_ids;
    }
    inline std::vector<u32> geom_shader_ids(void) {
      return this->_geom_shader_ids;
    }
    inline std::vector<u32> frag_shader_ids(void) {
      return this->_frag_shader_ids;
    }
    inline std::vector<u32> comp_shader_ids(void) {
      return this->_comp_shader_ids;
    }
    inline u32 program_id(void) {
      return this->_program_id;
    }
  private:
    ShaderType shader_type = vert_frag_shader;
    std::vector<std::string> vert_shader_paths;
    std::vector<std::string> frag_shader_paths;
    std::vector<std::string> geom_shader_paths;
    std::vector<std::string> comp_shader_paths;
    std::vector<u32> _vert_shader_ids;
    std::vector<u32> _geom_shader_ids;
    std::vector<u32> _frag_shader_ids;
    std::vector<u32> _comp_shader_ids;
    u32 _program_id = 0;
  };

  /**
   * @brief Loads shaders from an array of paths to a single shader.
   * Wrapper of OpenGL shader creation, with error checking. Will crash the program on error.
   * @param shader_path: array of paths of shader files from working directory.
   * @param shader_type: the type of shader to input to OpenGL. Such as GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc.
   * @param error_size: size of array for OpenGL error output.
   * @return shader_ids: id of created shader.
   */
  u32 load_shader(std::vector<std::string> shader_paths, u32 shader_type, u32 error_size = 1024);
}
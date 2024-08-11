#pragma once

// GL
#include <GL/glew.h>
#include <GL/glu.h>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/defines/config.hpp"

// EXTERNAL LIBS
#include <string>
#include <vector>

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
    Shader(std::vector<std::string> const &vert_shader_paths, std::vector<std::string> const &frag_shader_paths, types::u32 error_size = SHADER_DEFAULT_ERROR_SIZE);
    Shader(std::vector<std::string> const &vert_shader_paths, std::vector<std::string> const &geom_shader_paths, std::vector<std::string> const &frag_shader_paths, types::u32 error_size = SHADER_DEFAULT_ERROR_SIZE);
    Shader(std::vector<std::string> const &comp_shader_paths, types::u32 error_size = SHADER_DEFAULT_ERROR_SIZE);
    inline void use(void) {
      glUseProgram(_program_id);
      return;
    }
    inline types::u32 vert_shader_ids(void) {
      return this->_vert_shader_id;
    }
    inline types::u32 geom_shader_ids(void) {
      return this->_geom_shader_id;
    }
    inline types::u32 frag_shader_ids(void) {
      return this->_frag_shader_id;
    }
    inline types::u32 comp_shader_ids(void) {
      return this->_comp_shader_id;
    }
    inline types::u32 program_id(void) {
      return this->_program_id;
    }
  private:
    ShaderType _shader_type = vert_frag_shader;
    std::vector<std::string> _vert_shader_paths;
    std::vector<std::string> _frag_shader_paths;
    std::vector<std::string> _geom_shader_paths;
    std::vector<std::string> _comp_shader_paths;
    types::u32 _vert_shader_id = 0;
    types::u32 _geom_shader_id = 0;
    types::u32 _frag_shader_id = 0;
    types::u32 _comp_shader_id = 0;
    types::u32 _program_id = 0;
  };

  /**
   * @brief Loads shaders from an array of paths to a single shader.
   * Wrapper of OpenGL shader creation, with error checking. Will crash the program on error.
   * @param shader_path: array of paths of shader files from working directory.
   * @param shader_type: the type of shader to input to OpenGL. Such as GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc.
   * @param error_size: size of array for OpenGL error output.
   * @return id of created shader.
   */
  types::u32 load_shader(std::vector<std::string> const &shader_paths, types::u32 shader_type, types::u32 error_size = SHADER_DEFAULT_ERROR_SIZE);

  /**
   * @brief Creates a program with shaders attached.
   * Wrapper of OpenGL shader to program linking, with error checking. Will crash the program on error.
   * @param shaders: array of shader ids loaded and compiled.
   * @param error_size: size of array for OpenGL error output.
   * @return id of created program.
   */
  types::u32 load_program(std::vector<types::u32> const &shaders, types::u32 error_size = SHADER_DEFAULT_ERROR_SIZE);
}
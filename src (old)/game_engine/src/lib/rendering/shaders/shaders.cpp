#include "game_engine/src/lib/rendering/shaders/shaders.hpp"

// GL
#include <GL/glew.h>
#include <GL/glu.h>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/utils/error_handling.hpp"

// EXTERN LIBS
#include <string>
#include <vector>

namespace rendering {
  using namespace std;
  using namespace types;

  Shader::Shader(vector<string> const &vert_shader_paths, vector<string> const &frag_shader_paths, u32 error_size) {
    _shader_type = vert_frag_shader;
    _vert_shader_paths = vert_shader_paths;
    _vert_shader_id = load_shader(vert_shader_paths, GL_VERTEX_SHADER, error_size);
    _frag_shader_paths = frag_shader_paths;
    _frag_shader_id = load_shader(frag_shader_paths, GL_FRAGMENT_SHADER, error_size);
    _program_id = load_program({_vert_shader_id, _frag_shader_id}, error_size);
    return;
  }
  Shader::Shader(vector<string> const &vert_shader_paths, vector<string> const &geom_shader_paths, vector<string> const &frag_shader_paths, u32 error_size) {
    _shader_type = vert_geom_frag_shader;
    _vert_shader_paths = vert_shader_paths;
    _vert_shader_id = load_shader(vert_shader_paths, GL_VERTEX_SHADER, error_size);
    _geom_shader_paths = geom_shader_paths;
    _geom_shader_id = load_shader(geom_shader_paths, GL_GEOMETRY_SHADER, error_size);
    _frag_shader_paths = frag_shader_paths;
    _frag_shader_id = load_shader(frag_shader_paths, GL_FRAGMENT_SHADER, error_size);
    _program_id = load_program({_vert_shader_id, _geom_shader_id, _frag_shader_id}, error_size);

  }
  Shader::Shader(vector<string> const &comp_shader_paths, u32 error_size) {
    _shader_type = comp_shader;
    _comp_shader_paths = comp_shader_paths;
    _comp_shader_id = load_shader(comp_shader_paths, GL_COMPUTE_SHADER, error_size);
    _program_id = load_program({_comp_shader_id}, error_size);
  }

  u32 load_shader(vector<string> const &shader_paths, u32 shader_type, u32 error_size) {
    // vector of strings to c char* arr[]
    vector<const char*> c_strs;
    vector<GLint> str_lengths;
    for (int i = 0; i < shader_paths.size(); i++) {
      c_strs.push_back(shader_paths[i].data());
      str_lengths.push_back(shader_paths[i].size());
    }

    u32 shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, shader_paths.size(), c_strs.data(), str_lengths.data());
    glCompileShader(shader_id);

    // check success of shader compilation
    int compilation_sucess = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation_sucess);
    if (!compilation_sucess) {
      string gl_error_info;
      gl_error_info.resize(error_size);
      glGetShaderInfoLog(shader_id, error_size, NULL, gl_error_info.data());
      utils::panic(format("Error compiling shaders. GL Error: {}", gl_error_info), __PRETTY_FUNCTION__);
      return 0;
    }

    return shader_id;
  }

  u32 load_program(vector<u32> const &shaders, u32 error_size) {
    u32 program_id = glCreateProgram();
    for (int i = 0; i < shaders.size(); i++) {
      glAttachShader(program_id, shaders[i]);
    }
    glLinkProgram(program_id);

    // check success of linking
    int linking_success = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linking_success);
    if (!linking_success) {
      string gl_error_info;
      gl_error_info.resize(error_size);
      glGetProgramInfoLog(program_id, error_size, NULL, gl_error_info.data());
      utils::panic(format("Error linking shaders to program. GL Error: {}", gl_error_info), __PRETTY_FUNCTION__);
      return 0;
    }

    return program_id;
  }
}
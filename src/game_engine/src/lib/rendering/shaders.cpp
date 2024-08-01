#pragma once

#include "lib/rendering/shaders.hpp"

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
  using namespace std;
  Shader::Shader(vector<string> vert_shader_paths, vector<string> frag_shader_paths) {
    _program_id = glCreateProgram();
  }
  Shader::Shader(vector<string> vert_shader_paths, vector<string> geom_shader_paths, vector<string> frag_shader_paths) {

  }
  Shader::Shader(vector<string> comp_shader_paths) {

  }

  u32 load_shader(vector<string> shader_paths, u32 shader_type, u32 error_size) {
    // vector of strings to c char* arr[]
    vector<char*> c_strs;
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
      char* gl_error_info = new char[error_size];
      glGetShaderInfoLog(shader_id, error_size, NULL, gl_error_info);
    }
  }
}
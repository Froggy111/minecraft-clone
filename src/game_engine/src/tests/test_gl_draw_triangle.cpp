#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <array>
#include <vector>

uint32_t window_flags = SDL_WINDOW_OPENGL;
int window_width = 1000;
int window_height = 1000;
int gl_major_version = 4;
int gl_minor_version = 6;
const int use_glew_experimental = GL_TRUE;

SDL_Window* window = NULL;
SDL_GLContext gl_context = NULL;
SDL_Event sdl_event;

unsigned int gl_vertex_shader, gl_fragment_shader, gl_shader_program;
GLuint gl_VBO, gl_VAO;
const char* gl_vertex_shader_source = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char* gl_fragment_shader_source = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

bool init();
bool init_opengl();
bool init_buffers();
bool render();
bool render_init();

int main() {
  if (!init()) {
    printf("Initialisation failed\n");
    return 0;
  }
  init_buffers();
  render_init();
  while (true) {
    SDL_PollEvent(&sdl_event);
    if (sdl_event.type == SDL_WINDOWEVENT && sdl_event.window.event == SDL_WINDOWEVENT_CLOSE) {
      break;
    }
    render();
    SDL_GL_SwapWindow(window);
  }
  return 0;
}

bool init() {
  // initialise SDL2
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL2 failed to initialise. Error: %s\n", SDL_GetError());
    return false;
	}
  printf("SDL2 initialised.\n");
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major_version);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor_version);
  window = SDL_CreateWindow("OpenGL Test", 0, 0, window_width, window_height, window_flags);
  if (!window) {
    printf("SDL2 window failed to initialise. Error:%s\n", SDL_GetError());
    return false;
  }
  printf("SDL2 window initialised.\n");
  gl_context = SDL_GL_CreateContext(window);
  if (!gl_context) {
    printf("SDL2 OpenGL context failed to initialise. Error:%s\n", SDL_GetError());
    return false;
  }
  printf("SDL2 OpenGL context initialised.\n");
  int gl_major_version, gl_minor_version;
  // SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_major_version);
  // SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_minor_version);
  // printf("GL major version: %s\n", gl_major_version);
  // printf("GL minor version: %s\n", gl_minor_version);

  // initialise GLEW
  glewExperimental = use_glew_experimental;
  GLenum glew_error = glewInit();
  if (glew_error != GLEW_OK) {
    printf("Error initializing GLEW! %s\n", glewGetErrorString(glew_error));
    return false;
  }
  printf("GLEW initialised.\n");

  // initialise OpenGL
  if (!init_opengl()) {
    return false;
  }
  printf("OpenGL shaders initialised.\n");

  return true;
}

bool init_opengl() {
  // vertex shader
  gl_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(gl_vertex_shader, 1, &gl_vertex_shader_source, NULL);
  glCompileShader(gl_vertex_shader);
  int compilation_success = 0;
  glGetShaderiv(gl_vertex_shader, GL_COMPILE_STATUS, &compilation_success);
  if (!compilation_success) {
    char gl_error_info[512];
    glGetShaderInfoLog(gl_vertex_shader, 512, NULL, gl_error_info);
    printf("OpenGL vertex shader compilation failed. Error: %s\n", gl_error_info);
    return false;
  }

  // fragment shader
  gl_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(gl_fragment_shader, 1, &gl_fragment_shader_source, NULL);
  glCompileShader(gl_fragment_shader);
  compilation_success = 0;
  glGetShaderiv(gl_fragment_shader, GL_COMPILE_STATUS, &compilation_success);
  if (!compilation_success) {
    char gl_error_info[512];
    glGetShaderInfoLog(gl_fragment_shader, 512, NULL, gl_error_info);
    printf("OpenGL fragment shader compilation failed. Error: %s\n", gl_error_info);
    return false;
  }

  // shader program
  gl_shader_program = glCreateProgram();
  glAttachShader(gl_shader_program, gl_vertex_shader);
  glAttachShader(gl_shader_program, gl_fragment_shader);
  glLinkProgram(gl_shader_program);
  compilation_success = 0;
  glGetProgramiv(gl_shader_program, GL_LINK_STATUS, &compilation_success);
  if (!compilation_success) {
    char gl_error_info[512];
    glGetProgramInfoLog(gl_shader_program, 512, NULL, gl_error_info);
    printf("OpenGL shader program link failed. Error: %s\n", gl_error_info);
    return false;
  }

  return true;
}

bool init_buffers() {
  glGenVertexArrays(1, &gl_VAO);
  glGenBuffers(1, &gl_VBO);
  glBindVertexArray(gl_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, gl_VBO);
  return true;
}

bool render_init() {
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);
  return true;
}

bool render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(gl_shader_program);
  glBindVertexArray(gl_VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  return true;
}
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <chrono>

int window_width = 1000;
int window_height = 1000;
int gl_major_version = 4;
int gl_minor_version = 6;
const int use_glew_experimental = GL_TRUE;

GLFWwindow* window = NULL;

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
  glfwSwapInterval(0);
  int counter = 0;
  double t_start = glfwGetTime();
  while (!glfwWindowShouldClose(window)) {
    render();
    glfwSwapBuffers(window);
    glfwPollEvents();
    counter += 1;
  }
  double t_end = glfwGetTime();
  float fps = counter / (t_end - t_start);
  std::cout << std::format("Total runtime: {}\nTotal frames: {}\nFPS: {}\n", t_end - t_start, counter, fps) << std::endl;
  return 0;
}

bool init() {
  // initialise GLFW
  if (!glfwInit()) {
    printf("Error initialising GLFW!\n");
    return false;
  }

  printf("GLFW initialised\n");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major_version);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor_version);

  window = glfwCreateWindow(1000, 1000, "GLFW Test Window", NULL, NULL);
  if (!window) {
    glfwTerminate();
    printf("Error initialising GLFW window!\n");
    return false;
  }

  glfwMakeContextCurrent(window);

  // initialise GLEW
  glewExperimental = use_glew_experimental;
  GLenum glew_error = glewInit();
  if (glew_error != GLEW_OK) {
    glfwTerminate();
    printf("Error initializing GLEW! %s\n", glewGetErrorString(glew_error));
    return false;
  }
  printf("GLEW initialised.\n");

  // initialise OpenGL
  if (!init_opengl()) {
    glfwTerminate();
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
  glBindVertexArray(gl_VAO);
  glGenBuffers(1, &gl_VBO);
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
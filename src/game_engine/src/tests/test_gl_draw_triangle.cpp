// graphics libs
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <vector>
#include <array>
#include <iostream>

int main() {
  float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 1.0f,
     0.0f,  0.5f, 0.0f, 1.0f
  };

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  const char *vertex_shader_source =
      "#version 460 core"
      "layout(location = 0) in vec4 aPos;"
      "void main() {"
      "  gl_Position = aPos;"
      "}";

  const char *fragment_shader_source =
      "#version 460 core"
      "out vec4 frag_color_out;"
      "void main() {"
      "  frag_color_out = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
      "}";

  return 0;
}
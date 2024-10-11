#pragma once

// GL
#include <GL/glew.h>
#include <GL/glu.h>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/defines/config.hpp"
#include "game_engine/src/lib/rendering/buffers/vbo.hpp"
#include "game_engine/src/lib/rendering/buffers/ebo.hpp"

// EXTERNAL LIBS
#include <string>
#include <vector>


namespace rendering {
  class VAO {
  public:
    VAO();
    ~VAO();
    void use();
  private:
    types::u32 _id;
    VBO* _vbo = NULL;
    EBO* _ebo = NULL;
  };
}
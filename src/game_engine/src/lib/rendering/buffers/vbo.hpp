#pragma once

// GL
#include <GL/glew.h>
#include <GL/glu.h>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/defines/config.hpp"
#include "game_engine/src/lib/rendering/buffers/vao.hpp"

// EXTERNAL LIBS
#include <string>
#include <vector>


namespace rendering {
  /**
   * @brief Base class for VBO. 
   */
  class VBO {
  public:
    VBO();
    VBO(types::u32 id);
    ~VBO();
    void vertex_attrib_pointer(GLuint index,
                               GLint size,
                               GLenum type,
                               bool norm,
                               GLsizei stride,
                               const void* offset,
                               const VAO &vao);
    void bind(void);
  private:
    types::u32 _id;
  };
}
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
#include "external/result.hpp"

namespace rendering {
  VBO::VBO() {
    glGenBuffers(1, &_id);
  }

  VBO::VBO(types::u32 id) {
    _id = id;
    return;
  }

  VBO::~VBO() {
    glDeleteBuffers(1, &_id);
    return;
  }
  
  void vertex_attrib_pointer(GLuint index,
                             GLint size,
                             GLenum type,
                             bool norm,
                             GLsizei stride,
                             const void* offset,
                             const VAO &vao) {
      glVertexAttribPointer(index, size, type, norm, stride, offset);
    }
}
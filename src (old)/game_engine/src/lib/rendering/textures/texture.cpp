#include "game_engine/src/lib/rendering/textures/texture.hpp"

// GL
#include <GL/glew.h>
#include <GL/glu.h>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/defines/config.hpp"

// EXTERNAL LIBS
#include <string>

namespace rendering {
  using namespace std;
  using namespace types;

  Texture2D::Texture2D(string const &texture_path, int req_comp, int texture_level, int texture_internal_format, int texture_data_format) {
    types::byte* data = stbi_load(texture_path.data(), &_width, &_height, &_n_channels, req_comp);
    glGenTextures(1, &_texture_id);
    glBindTexture(GL_TEXTURE_2D, _texture_id);
    glTexImage2D(GL_TEXTURE_2D, texture_level, texture_internal_format, _width, _height, 0, texture_data_format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return;
  }

  Texture2D::~Texture2D(void) {
    glDeleteTextures(1, &_texture_id);
    return;
  }
}
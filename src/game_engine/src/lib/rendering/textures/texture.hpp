#pragma once

// GL
#include <GL/glew.h>
#include <GL/glu.h>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/defines/config.hpp"

// EXTERNAL LIBS
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

namespace rendering {
  /**
   * @brief Generic wrapper for a 2D OpenGL texture.
   */
  class Texture2D {
  public:
    /**
     * @brief Loads a 2D OpenGL texture from an image file.
     * @param texture_path: path to texture image file from current working directory.
     * @param req_comp: number of channels in the image.
     * @param texture_level: mipmap level of loaded texture. Level 0 is the base image level. Level n is the nth mipmap reduction image.
     * @param texture_internal_format: internal format of the loaded texture.
     * @param texture_data_format: format of the data loaded from image.
     */
    Texture2D(std::string const &texture_path, int req_comp = 0, int texture_level = 0, int texture_internal_format = GL_RGB, int texture_data_format = GL_RGB);
    
    ~Texture2D(void);

    inline void use(void) {
      glBindTexture(GL_TEXTURE_2D, this->_texture_id);
      return;
    }

    inline int width(void) {
      return this->_width;
    }
    inline int height(void) {
      return this->_height;
    }
    inline int n_channels(void) {
      return this->_n_channels;
    }
    inline types::u32 texture_id(void) {
      return this->_texture_id;
    }
  private:
    int _width;
    int _height;
    int _n_channels;

    types::u32 _texture_id;
  };
}
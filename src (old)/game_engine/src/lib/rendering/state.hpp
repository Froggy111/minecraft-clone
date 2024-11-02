/**
 * Wrappers for OpenGL bindings. Not very necessary, but ensures that binding is fast even on bad driver implementations.
 */

#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/utils/error_handling.hpp"

namespace rendering {
  enum class bindStatus {
    failed = 0,
    bound = 1,
    unchanged = 2,
  };

  // buffer objects
  bindStatus bind_VAO(types::u32 VAO); void unbind_VAO(void);
  bindStatus bind_VBO(types::u32 VBO); void unbind_VBO(void);
  bindStatus bind_EBO(types::u32 EBO); void unbind_EBO(void);
  bindStatus bind_texture(types::u32 texture); void unbind_texture(void);
  bindStatus bind_uniform(types::u32 uniform); void unbind_uniform(void);

  // shaders
  bindStatus bind_shader(types::u32 shader); void unbind_shader(void);
}
#include "game_engine/src/lib/rendering/state.hpp"

// GL
#include <GL/glew.h>
#include <GL/glu.h>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/utils/error_handling.hpp"

namespace rendering {
  using namespace types;

  //* BUFFER OBJECTS
  // VAO 
  int binded_VAO = 0;
  /**
   * @brief Wrapper for binding a VAO, with own state machine implementation. Checks if VAO is already bound to reduce driver calls.
   * @param VAO: ID of the VAO to bind.
   * @return bound if new VAO is bound, unchanged if binding the same VAO.
   */
  bindStatus bind_VAO(u32 VAO) {
    if (VAO != binded_VAO) {
      glBindVertexArray(VAO);
      binded_VAO = VAO;
      return bindStatus::bound;
    }
    return bindStatus::unchanged;
  }
  /**
   * @brief Wrapper for "unbinding" a VAO. Should be very rarely used (usually, no need to unbind, only adds unnecessary driver calls)
   */
  void unbind_VAO(void) {
    glBindVertexArray(0);
    binded_VAO = 0;
    return;
  }

  // VBO
  int binded_VBO = 0;
  /**
   * @brief Wrapper for binding a VBO, with own state machine implementation. Checks if VBO is already bound to reduce driver calls.
   * If no VAO is bound, panics.
   * @param VBO: ID of the VBO to bind.
   * @return bound if new VBO is bound, unchanged if binding the same VBO.
   */
  bindStatus bind_VBO(u32 VBO) {
    if (binded_VAO == 0) {
      utils::panic(std::format("Tried to bind VBO {} when VAO is unbound."), __PRETTY_FUNCTION__);
    }
    if (VBO != binded_VBO) { 
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      binded_VBO = VBO;
      return bindStatus::bound;
    }
    return bindStatus::unchanged;
  }
  /**
   * @brief Wrapper for binding a VBO, with own state machine implementation. Checks if VBO is already bound to reduce driver calls.
   * If no VAO is bound, returns failed instead of crashing.
   * @param VBO: ID of the VBO to bind.
   * @return bound if new VBO is bound, unchanged if binding the same VBO, failed if binding without VAO. 
   */
  bindStatus bind_VBO_no_crash(u32 VBO) {
    if (binded_VAO == 0) {
      return bindStatus::failed;
    }
    if (VBO != binded_VBO) { 
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      binded_VBO = VBO;
      return bindStatus::bound;
    }
    return bindStatus::unchanged;
  } 
   /**
   * @brief Wrapper for "unbinding" a VBO. Should be very rarely used (usually, no need to unbind, only adds unnecessary driver calls)
   */
  void unbind_VBO(void) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    binded_VBO = 0;
    return;
  }

  // EBO
  int binded_EBO = 0;
  /**
   * @brief Wrapper for binding a EBO, with own state machine implementation. Checks if EBO is already bound to reduce driver calls.
   * If no VAO is bound, panics.
   * @param EBO: ID of the EBO to bind.
   * @return bound if new EBO is bound, unchanged if binding the same EBO.
   */
  bindStatus bind_EBO(u32 EBO) {
    if (binded_VAO == 0) {
      utils::panic(std::format("Tried to bind EBO {} when VAO is unbound."), __PRETTY_FUNCTION__);
    }
    if (EBO != binded_EBO) { 
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      binded_EBO = EBO;
      return bindStatus::bound;
    }
    return bindStatus::unchanged;
  }
  /**
   * @brief Wrapper for binding a EBO, with own state machine implementation. Checks if EBO is already bound to reduce driver calls.
   * If no VAO is bound, returns failed instead of crashing.
   * @param EBO: ID of the EBO to bind.
   * @return bound if new EBO is bound, unchanged if binding the same EBO, failed if binding without VAO. 
   */
  bindStatus bind_EBO_no_crash(u32 EBO) {
    if (binded_VAO == 0) {
      return bindStatus::failed;
    }
    if (EBO != binded_EBO) { 
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      binded_EBO = EBO;
      return bindStatus::bound;
    }
    return bindStatus::unchanged;
  } 
   /**
   * @brief Wrapper for "unbinding" a EBO. Should be very rarely used (usually, no need to unbind, only adds unnecessary driver calls)
   */
  void unbind_EBO(void) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    binded_EBO = 0;
    return;
  }

}
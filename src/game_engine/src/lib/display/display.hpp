#pragma once

// GL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <GL/glu.h>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/defines/config.hpp"

// EXTERNAL LIBS
#include <string>
#include <vector>
#include "spdlog/spdlog.h"

namespace display {
  class Window {
  public:
    /**
     * @brief Create a window using a GL context from another window, and in fullscreen on a selected monitor.
     * NOTE: Does NOT switch context to window. Call .use() to switch context to this window.
     * @param width: Width of window to create.
     * @param height: Height of window to create.
     * @param name: Name of window to create.
     * @param gl_major_version: The major version of OpenGL context to use for this window. Game is developed with major version 4.
     * @param gl_minor_version: The minor version of OpenGL context to use for this window. Game is developed with minor version 6.
     * @param fullscreen: Whether to start the window in fullscreen. Defaults to false.
     * @param monitor: The GLFW monitor this window fullscreens to. Defaults to primary monitor. Will crash the program if null.
     */
    Window(int width, int height, const std::string &name, int gl_major_version, int gl_minor_version, bool fullscreen = false, GLFWmonitor* monitor = glfwGetPrimaryMonitor());
    /**
     * @brief Create a window using a GL context from another window, and in fullscreen on a selected monitor.
     * NOTE: Does NOT switch context to window. Call .use() to switch context to this window.
     * @param width: Width of window to create.
     * @param height: Height of window to create.
     * @param name: Name of window to create.
     * @param gl_major_version: The major version of OpenGL context to use for this window. Game is developed with major version 4.
     * @param gl_minor_version: The minor version of OpenGL context to use for this window. Game is developed with minor version 6.
     * @param share: Another window to share an OpenGL context with.
     * @param fullscreen: Whether to start the window in fullscreen. Defaults to false.
     * @param monitor: The GLFW monitor this window fullscreens to. Defaults to primary monitor. Will crash the program if null.
     */
    Window(int width, int height, const std::string &name, int gl_major_version, int gl_minor_version, Window &share, bool fullscreen = false, GLFWmonitor* monitor = glfwGetPrimaryMonitor());

    ~Window(void);

    /**
     * @brief swaps buffers. Does not take into account target fps and vsync. Simply a wrapper for glfwSwapBuffers(window).
     */
    void swap_buffers_glfw(void) {
      glfwSwapBuffers(this->_window);
      return;
    }

    /**
     * @brief Toggles the window to fullscreen onto the currently set monitor.
     * @param borderless: Whether the fullscreen window should be borderless.
     */
    void fullscreen(bool borderless = true) {
      if(!this->_fullscreen) {
        glfwSetWindowMonitor(this->_window, this->_monitor, 0, 0, 0, 0, GLFW_DONT_CARE);
        this->_fullscreen = true;
      }
    }

    /**
     * @brief Change the monitor of the window. If in fullscreen mode, will set the window to fullscreen on the other window.
     * @param monitor: The monitor to change the window to.
     */
    void change_monitor(GLFWmonitor* monitor) {
      this->_monitor = monitor;
      if (this->_fullscreen) {
        glfwSetWindowMonitor(this->_window, this->_monitor, 0, 0, 0, 0, GLFW_DONT_CARE);
      }
    }

    /**
     * @brief Switches the OpenGL context to this window.
     */
    inline void use(void) {
      glfwMakeContextCurrent(this->_window);
      return;
    }

    /**
     * @brief Detaches the OpenGL context of the current window.
     * Checks to make sure that the attempted detatch is this window. If not, crashes the program.
     * Unnecessary if simply switching OpenGL contexts.
     */
    inline void detach(void) {
      GLFWwindow* context_window = glfwGetCurrentContext();
      if (context_window != this->_window) {
        std::string context_window_name = glfwGetWindowTitle(context_window);
        utils::panic(format("Attempted to detach context of window \"{}\" from the window \"{}\"", context_window_name, this->_name), __PRETTY_FUNCTION__);
        return;
      }
      glfwMakeContextCurrent(NULL);
      return;
    }

    inline GLFWwindow* window(void) {
      return this->_window;
    }
    inline int gl_major_version(void) {
      return this->_gl_major_version;
    }
    inline int gl_minor_version(void) {
      return this->_gl_minor_version;
    }
    inline int width(void) {
      return this->_width;
    }
    inline int height(void) {
      return this->_height;
    }
    inline std::string name(void) {
      return this->_name;
    }

    inline Window* linked_window(void) {
      return this->_linked_window;
    }
    inline GLFWmonitor* monitor(void) {
      return this->_monitor;
    }

    inline bool is_fullscreen(void) {
      return this->_fullscreen;
    }
  private:
    GLFWwindow* _window = NULL;
    int _gl_major_version = 0;
    int _gl_minor_version = 0;
    int _width = 0;
    int _height = 0;
    std::string _name = "";

    Window* _linked_window = NULL;
    GLFWmonitor* _monitor = NULL;

    bool _fullscreen = false;
    bool _vsync = true;
    int _target_fps = 60;
    int _swap_interval = 1;
  };

  /**
   * @brief Wrapper for initialising glew, with error checking included.
   * Will crash program on error.
   * Should be called before any OpenGL functions are used.
   */
  void init_glew();

  /**
   * @brief Wrapper for initialising glfw, with error checking included.
   * Will crash program on error.
   * Should be called before any GLFW functions are used.
   */
  void init_glfw();
}
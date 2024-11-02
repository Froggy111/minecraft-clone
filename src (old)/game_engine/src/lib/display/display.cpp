#include "game_engine/src/lib/display/display.hpp"

// GL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <GL/glu.h>

// LIBS
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/defines/config.hpp"
#include "game_engine/src/lib/utils/error_handling.hpp"

// EXTERNAL LIBS
#include <string>
#include <vector>
#include "spdlog/spdlog.h"

namespace display {
  using namespace std;
  using namespace utils;

  void init_glew() {
    glewExperimental = USE_GLEW_EXPERIMENTAL;
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK) {
      glfwTerminate();
      string err_msg = format("Error initialising GLEW: {}", string((char*) glewGetErrorString(glew_error)));
      spdlog::critical(err_msg);
      panic(err_msg, __PRETTY_FUNCTION__);
      return;
    }
    spdlog::info("Successfully initialised GLEW.");
    return;
  }

  void init_glfw() {
    bool init_success = glfwInit();
    if (!init_success) {
      const char* err_description;
      int err_code = glfwGetError(&err_description);
      string err_description_str(err_description);
      string err_msg = format("Error initialising GLFW. Error code: {}. Error description: {}", err_code, err_description_str);
      spdlog::critical(err_msg);
      panic(err_msg, __PRETTY_FUNCTION__);
      return;
    }
    spdlog::info("Successfully initialised GLFW.");
    return;
  }

  /**
   * @brief Wrapper for creating a GLFW window with error checking and logging. Will crash the program on error.
   * NOTE: Does NOT switch context to window. 
   */
  GLFWwindow* create_glfw_window(int width, int height, const string &name, int gl_major_version, int gl_minor_version, GLFWmonitor* monitor, GLFWwindow* share) {
    GLFWwindow* window = NULL;
    
    window = glfwCreateWindow(width, height, name.data(), monitor, share);
    string monitor_name;
    if (monitor) {
      monitor_name = glfwGetMonitorName(monitor);
    }
    else {
      monitor_name = "NULL";
    }
    string share_name;
    if (share) {
      share_name = glfwGetWindowTitle(share);
    }
    else {
      share_name = "NULL";
    }
    if (!window) {
      glfwTerminate();
      string err_msg = format("Error creating window. Width: {}. Height: {}. Name: {}. Monitor: {}. Share: {}. GL version: {}.{}",
                              width, height, name, monitor_name, share_name, gl_major_version, gl_minor_version);
      spdlog::critical(err_msg);
      panic(err_msg, __PRETTY_FUNCTION__);
      return NULL;
    }
    spdlog::debug(format("Successfully created GLFW window. Width: {}. Height: {}. Name: {}. Monitor: {}. Share: {}. GL version: {}.{}",
                       width, height, name, monitor_name, share_name, gl_major_version, gl_minor_version));
    return window;
  }
  
  Window::Window(int width, int height, const string &name, int gl_major_version, int gl_minor_version, bool fullscreen, GLFWmonitor* monitor) {
    if (!monitor) {
      panic(format("Tried to create window with null monitor. Width: {}. Height: {}. Name: {}. Share: {}. GL version: {}.{}",
                   width, height, name, "NULL", gl_major_version, gl_minor_version), __PRETTY_FUNCTION__);
      return;
    }
    GLFWmonitor* fullscreen_monitor = NULL;
    if (fullscreen) {
      fullscreen_monitor = monitor;
      _fullscreen = true;
    }
    _window = create_glfw_window(width, height, name, gl_major_version, gl_minor_version, fullscreen_monitor, NULL);
    _width = width;
    _height = height;
    _name = name;
    _gl_major_version = gl_major_version;
    _gl_minor_version = gl_minor_version;
    _linked_window = NULL;
    _monitor = monitor;
    return;
  }

  Window::Window(int width, int height, const string &name, int gl_major_version, int gl_minor_version, Window &share, bool fullscreen, GLFWmonitor* monitor) {
    if (!monitor) {
      panic(format("Tried to create window with null monitor. Width: {}. Height: {}. Name: {}. Share: {}. GL version: {}.{}",
                   width, height, name, share.name(), gl_major_version, gl_minor_version), __PRETTY_FUNCTION__);
      return;
    }
    GLFWmonitor* fullscreen_monitor = NULL;
    if (fullscreen) {
      fullscreen_monitor = monitor;
      _fullscreen = true;
    }
    _window = create_glfw_window(width, height, name, gl_major_version, gl_minor_version, fullscreen_monitor, share.window());
    _width = width;
    _height = height;
    _name = name;
    _gl_major_version = gl_major_version;
    _gl_minor_version = gl_minor_version;
    _linked_window = &share;
    _monitor = monitor;
    return;
  }

  Window::~Window(void) {
    glfwDestroyWindow(this->_window);
  }
}
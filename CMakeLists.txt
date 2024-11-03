cmake_minimum_required(VERSION 3.25)
project(Minecraft, CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add module support
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message(STATUS "Using GCC")
  set(DEFAULT_CMAKE_CXX_FLAGS "-fmodules-ts") # This does not work with clangd!
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message(STATUS "Using Clang")
  set(DEFAULT_CMAKE_CXX_FLAGS "-fmodules")
else()
  message(STATUS "Using an unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Other default flags
set(DEFAULT_CMAKE_CXX_FLAGS "${DEFAULT_CMAKE_CXX_FLAGS} -fno-rtti")
set(CMAKE_CXX_FLAGS "${DEFAULT_CMAKE_CXX_FLAGS} ${PRESET_CMAKE_CXX_FLAGS}")

# Thread lib (to get it working with clang)
set(CMAKE_THREAD_LIBS_INIT "pthread")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build flags: ${CMAKE_CXX_FLAGS}")


# EXTENRAL LIBS
# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
message(STATUS "OpenGL found at ${OPENGL_INCLUDE_DIR}")
# GLM
find_package(glm REQUIRED)
# GLEW
find_package(GLEW REQUIRED)
message(STATUS "GLEW found at ${GLEW_INCLUDE_DIR}")
# SDL2
find_package(SDL2 REQUIRED)
message(STATUS "SDL2 found at ${SDL2_INCLUDE_DIRS}")
# GLFW
find_package(glfw3 REQUIRED)
# SPDLog
find_package(spdlog REQUIRED)

add_subdirectory("src")
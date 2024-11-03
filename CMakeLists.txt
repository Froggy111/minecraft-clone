cmake_minimum_required(VERSION 3.30)
project(Minecraft, CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULES ON)

set(DEFAULT_BUILD_TYPE Release)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type specified. Defaulting to ${DEFAULT_BUILD_TYPE}")
  set(CMAKE_BUILD_TYPE DEFAULT_BUILD_TYPE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O1 -DDEBUG -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -march=native -funroll-loops -flto")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -DNDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

# custom build types for performance profiling
set(CMAKE_CXX_FLAGS_FAST "-DPROFILING -O2 -march=native -funroll-loops")
set(CMAKE_CXX_FLAGS_MAXOPT "-DPROFILING -O3 -march=native -funroll-loops -flto -ffast-math")
if(CMAKE_BUILD_TYPE STREQUAL "ProfilingFast")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_FAST}")
elseif(CMAKE_BUILD_TYPE STREQUAL "ProfilingMaxOpt")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_MAXOPT}")
endif()

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
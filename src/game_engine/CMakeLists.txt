cmake_minimum_required(VERSION 3.2)
project(
  MinecraftGameEngine
  VERSION 0.0
  LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories("src")

# DISPLAY LIBRARIES
# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
message(STATUS "OpenGL included at ${OPENGL_INCLUDE_DIR}")
# GLM
find_package(glm REQUIRED)
# include_directories(${PROJECT_NAME} PUBLIC ${GLM_INCLUDE_DIRS})
link_libraries(glm::glm)
# message(STATUS "GLM included at ${GLM_INCLUDE_DIRS}")
# GLEW
find_package(GLEW REQUIRED)
include_directories(${PROJECT_NAME} PUBLIC ${GLEW_INCLUDE_DIR})
message(STATUS "GLEW included at ${GLEW_INCLUDE_DIR}")
# SDL2
find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
message(STATUS "SDL2 included at ${SDL2_INCLUDE_DIRS}")

set(EXTERNAL_LIBS ${OPENGL_LIBRARIES} ${GLM_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES})
link_libraries(${EXTERNAL_LIBS})

# COMPILE SETTINGS
# Main library (game engine)
file(GLOB_RECURSE LIB_SOURCES "src/lib/*.cpp")
file(GLOB_RECURSE LIB_HEADERS "src/lib/*.hpp")
add_library(lib ${LIB_SOURCES} ${LIB_HEADERS})

# Tests for library
file(GLOB_RECURSE TEST_SOURCES "src/tests/*.cpp")
foreach(testsourcefile ${TEST_SOURCES})
  get_filename_component(testname ${testsourcefile} NAME_WE)
  add_executable(${testname}.o ${testsourcefile})
  get_filename_component(testdir ${testsourcefile} DIRECTORY)
  set_target_properties(${testname}.o PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${testdir})
  target_link_libraries(${testname}.o lib)
endforeach(testsourcefile ${TEST_SOURCES})

# Other misc files
file(GLOB APP_SOURCES "src/*.cpp")
foreach(appsourcefile ${APP_SOURCES})
  get_filename_component(appname ${appsourcefile} NAME_WE)
  add_executable(${appname}.o ${appsourcefile})
  get_filename_component(appdir ${appsourcefile} DIRECTORY)
  set_target_properties(${appname}.o PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${appdir})
  target_link_libraries(${appname}.o lib)
endforeach(appsourcefile ${APP_SOURCES})
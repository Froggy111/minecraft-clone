cmake_minimum_required(VERSION 3.2)
project(
  Minecraft
  VERSION 0.0
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories("./")

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
# GLFW
find_package(glfw3 REQUIRED)
link_libraries(glfw)

set(EXTERNAL_LIBS ${OPENGL_LIBRARIES} ${GLM_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES})
link_libraries(${EXTERNAL_LIBS})

# COMPILE SETTINGS
# Game engine
file(GLOB_RECURSE ENGINE_SOURCES "game_engine/src/lib/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "game_engine/src/lib/*.hpp")
add_library(engine ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Game engine tests
file(GLOB_RECURSE ENGINE_TEST_SOURCES "game_engine/src/tests/*.cpp")
foreach(engine_test_source_file ${ENGINE_TEST_SOURCES})
  get_filename_component(engine_test_name ${engine_test_source_file} NAME_WE)
  add_executable(${engine_test_name}.o ${engine_test_source_file})
  get_filename_component(engine_test_dir ${engine_test_source_file} DIRECTORY)
  set_target_properties(${engine_test_name}.o PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${engine_test_dir})
  target_link_libraries(${engine_test_name}.o engine)
endforeach(engine_test_source_file ${ENGINE_TEST_SOURCES})

# Mods
file(GLOB_RECURSE MOD_SOURCES "game/src/mods/*.cpp")
file(GLOB_RECURSE MOD_HEADERS "game/src/mods/*.cpp")
add_library(mods ${MOD_SOURCES} ${MOD_HEADERS})

# Mod tests
file(GLOB_RECURSE MOD_TEST_SOURCES "game/src/mods/tests/*.cpp")
foreach(mod_test_source_file ${MOD_TEST_SOURCES})
  get_filename_component(mod_test_name ${mod_test_source_file} NAME_WE)
  add_executable(${mod_test_name}.o ${mod_test_source_file})
  get_filename_component(mod_test_dir ${mod_test_source_file} DIRECTORY)
  set_target_properties(${mod_test_name}.o PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${mod_test_dir})
  target_link_libraries(${mod_test_name}.o engine mods)
endforeach(mod_test_source_file ${MOD_TEST_SOURCES})

# Other misc files
file(GLOB APP_SOURCES "*/src/*.cpp")
foreach(appsourcefile ${APP_SOURCES})
  get_filename_component(appname ${appsourcefile} NAME_WE)
  add_executable(${appname}.o ${appsourcefile})
  get_filename_component(appdir ${appsourcefile} DIRECTORY)
  set_target_properties(${appname}.o PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${appdir})
  target_link_libraries(${appname}.o engine)
endforeach(appsourcefile ${APP_SOURCES})
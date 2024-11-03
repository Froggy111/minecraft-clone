add_library(game_engine)
target_sources(game_engine
  PUBLIC
    FILE_SET CXX_MODULES FILES
      game_engine.cppm
  PRIVATE
    game_engine.cpp)

target_include_directories(game_engine PRIVATE ".")
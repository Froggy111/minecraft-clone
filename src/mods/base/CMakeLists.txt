add_library(mods_base)
target_sources(mods_base
  PUBLIC
    FILE_SET CXX_MODULES FILES
      mods_base.cppm
  PRIVATE
    mods_base.cpp)
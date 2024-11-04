add_library(stb_image)
target_sources(
  stb_image
  PUBLIC
    FILE_SET CXX_MODULES FILES
      stb_image.cppm
  PRIVATE
    stb_image.cpp
)
#include "game_engine/src/lib/utils/error_handling.hpp"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, const char *argv[]) {
  if (argc != 3) {
    utils::panic(
"\
Invalid args.\n\
Args:\
1. Window width (int)\
2. Window height (int)\
"
    , __PRETTY_FUNCTION__);
  }

  int width = std::stoi(argv[1]);
  int height = std::stoi(argv[2]);

  float mesh[] = {
    
  }
  return 0;
}
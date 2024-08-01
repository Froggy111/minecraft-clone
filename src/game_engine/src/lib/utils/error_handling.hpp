#include <string>
#include <iostream>

namespace utils {
  void panic(std::string err_msg, std::string func_name) {
    std::cout << std::format("Error raised by {}: {}", func_name, err_msg);
    exit(0);
    return;
  }
}
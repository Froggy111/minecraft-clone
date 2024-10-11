#pragma once

// LIBS
#include "game_engine/src/lib/defines/config.hpp"
#include "game_engine/src/lib/utils/time.hpp"

// EXTERNAL LIBS
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include "spdlog/spdlog.h"

namespace utils {
  void make_crash_file(std::string crash_dir, std::string crash_contents) {
    std::chrono::utc_clock clock;
    std::string time_str = utc_time_str(clock);
    std::string crash_file_path = std::format("{}/{}-CRASH.txt", crash_dir, time_str);
    std::string crash_file_contents = std::format("{}-CRASH: {}", time_str, crash_contents);
    std::fstream file_stream;
    file_stream.open(crash_file_path, std::fstream::app);
    file_stream.write(crash_file_contents.data(), crash_file_contents.size());
    file_stream.close();
    return;
  }

  /**
   * @brief Panics and exits the program. Outputs error message to std::cout and 
   * creates a crash file in PANIC_LOGDIR (configure in defines/configs/error_handling_conf.hpp)
   * @param err_msg: Error message. Do not add newline at the end, it is automatically added.
   * @param func_name: Name of function. Use the __PRETTY_FUNCTION__ macro.
   */
  void panic(std::string err_msg, std::string func_name) {
    spdlog::critical(std::format("Panic raised by {}: {}\n", func_name, err_msg));

    #ifdef PANIC_MAKE_CRASH_FILE
    make_crash_file(PANIC_LOGDIR, std::format("Panic raised by {}: {}\n", func_name, err_msg));
    #endif
    exit(EXIT_FAILURE);
    return;
  }
}
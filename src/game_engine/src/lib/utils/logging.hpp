#pragma once

// LIBS
#include "game_engine/src/lib/defines/config.hpp"
#include "game_engine/src/lib/defines/typedefs.hpp"
#include "game_engine/src/lib/utils/error_handling.hpp"

// EXTERNAL LIBS
#include <string>
#include <fstream>
#include <chrono>

namespace utils {
  void do_nothing(void) {return;}

  enum Severity {
    // decreasing in severity
    fatal_s,
    error_s,
    warning_s,
    notice_s,
    info_s,
    debug_s,
    trace
  };

  std::string severity_to_str(Severity severity) {
    switch (severity) {
      case fatal_s: return "FATAL";
      case error_s: return "ERROR";
      case warning_s: return "WARN";
      case notice_s: return "NOTICE";
      case info_s: return "INFO";
      case debug_s: return "DEBUG";
    }
    utils::panic(std::format("Invalid severity {} input to logger.", (int) severity), __PRETTY_FUNCTION__);
    return "INVALID";
  }

  enum LoggerMode {
    console = 1,
    file = 2
  };

  class Logger {
  public:
    /**
     * @brief Construct logger with configurable output modes.
     * @param logger_mode: Bitwise ORs of options in LoggerMode.
     * @param log_file_path: Path to output log file.
     */
    Logger(types::u32 logger_mode, std::string log_file_path = {}) {
      if ((logger_mode & file) && log_file_path.empty()) {
        // bad, crash program!
        panic("Tried to create logger with file output with empty file name.", __PRETTY_FUNCTION__);
        return;
      }
      if (!(logger_mode & file) && !log_file_path.empty()) {
        // filename given when no option to output to file, probably unintended activity!
        panic("Tried to create logger without file output with a file name.", __PRETTY_FUNCTION__);
        return;
      }

      if (!logger_mode) {
        // no option selected, probably unintended activity!
        panic("Tried to create logger without any output mode.", __PRETTY_FUNCTION__);
      }

      if (logger_mode & file) {
        // file mode selected
        file_out = true;
        file_stream.open(log_file_path, std::fstream::app);
      }
      if (logger_mode & console) {
        console_out = true;
      }
      return;
    }

    /**
     * @brief Debug log without timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void debug_nt(std::string log) {
      #ifdef LOGGER_ENABLE_DEBUG
      log = std::format("{}:{}\n", severity_to_str(debug_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Debug log with timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void debug(std::string log) {
      #ifdef LOGGER_ENABLE_DEBUG
      log = std::format("{},{}:{}\n", utc_time_str(clock), severity_to_str(debug_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Info log without timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void info_nt(std::string log) {
      #ifdef LOGGER_ENABLE_INFO
      log = std::format("{}:{}\n", severity_to_str(debug_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Info log with timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void info(std::string log) {
      #ifdef LOGGER_ENABLE_INFO
      log = std::format("{},{}:{}\n", utc_time_str(clock), severity_to_str(info_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Notice log without timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void notice_nt(std::string log) {
      #ifdef LOGGER_ENABLE_NOTICE
      log = std::format("{}:{}\n", severity_to_str(notice_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Notice log with timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void notice(std::string log) {
      #ifdef LOGGER_ENABLE_NOTICE
      log = std::format("{},{}:{}\n", utc_time_str(clock), severity_to_str(notice_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Warning log without timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void warn_nt(std::string log) {
      #ifdef LOGGER_ENABLE_WARNING
      log = std::format("{}:{}\n", severity_to_str(warning_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Warning log with timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void warn(std::string log) {
      #ifdef LOGGER_ENABLE_WARNING
      log = std::format("{},{}:{}\n", utc_time_str(clock), severity_to_str(warning_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Error log without timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void error_nt(std::string log) {
      #ifdef LOGGER_ENABLE_ERROR
      log = std::format("{}:{}\n", severity_to_str(error_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Error log with timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void error(std::string log) {
      #ifdef LOGGER_ENABLE_ERROR
      log = std::format("{},{}:{}\n", utc_time_str(clock), severity_to_str(error_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Fatal log without timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void fatal_nt(std::string log) {
      #ifdef LOGGER_ENABLE_FATAL
      log = std::format("{}:{}\n", severity_to_str(fatal_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Fatal log with timestamp.
     * @param log: Log message. Do not add newline at the end, it is automatically added.
     */
    inline void fatal(std::string log) {
      #ifdef LOGGER_ENABLE_FATAL
      log = std::format("{},{}:{}\n", utc_time_str(clock), severity_to_str(fatal_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

  private:
    std::fstream file_stream;
    bool console_out = false;
    bool file_out = false;
    std::chrono::utc_clock clock;
  };
}
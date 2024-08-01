#pragma once

// LIBS
#include "lib/defines/config.hpp"
#include "lib/defines/typedefs.hpp"
#include "lib/utils/error_handling.hpp"

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
      case fatal_s: return "Fatal";
      case error_s: return "Error";
      case warning_s: return "Warn";
      case notice_s: return "Notice";
      case info_s: return "Info";
      case debug_s: return "Debug";
    }
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
     * @param logfile: Path to output logfile
     */
    Logger(u32 logger_mode, std::string logfile = {}) {
      if ((logger_mode & file) && logfile.empty()) {
        // bad, crash program!
        panic("Tried to create logger with file output with empty file name.", __PRETTY_FUNCTION__);
        return;
      }
      if (!(logger_mode & file) && !logfile.empty()) {
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
        file_stream.open(logfile, std::fstream::app);
      }
      if (logger_mode & console) {
        console_out = true;
      }
      return;
    }

    /**
     * @brief Debug log without timestamp
     */
    inline void debug_nt(std::string log) {
      #ifdef LOGGER_ENABLE_DEBUG
      log = std::format("{}:{}", severity_to_str(debug_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Debug log with timestamp
     */
    inline void debug(std::string log) {
      #ifdef LOGGER_ENABLE_DEBUG
      auto time = clock.now();
      log = std::format("{} {}:{}", time, severity_to_str(debug_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Info log without timestamp
     */
    inline void info_nt(std::string log) {
      #ifdef LOGGER_ENABLE_INFO
      log = std::format("{}:{}", severity_to_str(debug_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Info log with timestamp
     */
    inline void info(std::string log) {
      #ifdef LOGGER_ENABLE_INFO
      auto time = clock.now();
      log = std::format("{} {}:{}", time, severity_to_str(info_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Notice log without timestamp
     */
    inline void notice_nt(std::string log) {
      #ifdef LOGGER_ENABLE_NOTICE
      log = std::format("{}:{}", severity_to_str(notice_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Notice log with timestamp
     */
    inline void notice(std::string log) {
      #ifdef LOGGER_ENABLE_NOTICE
      auto time = clock.now();
      log = std::format("{} {}:{}", time, severity_to_str(notice_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Warning log without timestamp
     */
    inline void warn_nt(std::string log) {
      #ifdef LOGGER_ENABLE_WARNING
      log = std::format("{}:{}", severity_to_str(warning_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Warning log with timestamp
     */
    inline void warn(std::string log) {
      #ifdef LOGGER_ENABLE_WARNING
      auto time = clock.now();
      log = std::format("{} {}:{}", time, severity_to_str(warning_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Error log without timestamp
     */
    inline void error_nt(std::string log) {
      #ifdef LOGGER_ENABLE_ERROR
      log = std::format("{}:{}", severity_to_str(error_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Error log with timestamp
     */
    inline void error(std::string log) {
      #ifdef LOGGER_ENABLE_ERROR
      auto time = clock.now();
      log = std::format("{} {}:{}", time, severity_to_str(error_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Fatal log without timestamp
     */
    inline void fatal_nt(std::string log) {
      #ifdef LOGGER_ENABLE_FATAL
      log = std::format("{}:{}", severity_to_str(fatal_s), log);
      if (file_out) {
        file_stream.write(log.data(), log.size());
      }
      if (console_out) {
        std::cout << log << std::endl;
      }
      #endif
    }

    /**
     * @brief Fatal log with timestamp
     */
    inline void fatal(std::string log) {
      #ifdef LOGGER_ENABLE_FATAL
      auto time = clock.now();
      log = std::format("{} {}:{}", time, severity_to_str(fatal_s), log);
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
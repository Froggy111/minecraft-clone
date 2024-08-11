#include <string>
#include <chrono>

namespace utils {
  std::string utc_time_str(std::chrono::utc_clock clock) {
    return std::format("{0:%F}T{0:%R%z}", clock.now());
  }
}
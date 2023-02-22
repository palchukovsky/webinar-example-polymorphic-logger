#pragma once

#include <string_view>

namespace PolymorphicLoggerExample {

class Logger {
 public:
  Logger() = default;
  Logger(const Logger &) = delete;
  Logger(Logger &&) = default;
  virtual ~Logger() = default;

  Logger &operator=(Logger &&) = default;
  Logger &operator=(const Logger &) = delete;

  virtual void writeMessage(std::string_view) = 0;

  [[nodiscard]] virtual std::string_view name() const = 0;
  [[nodiscard]] virtual size_t numberOfRecords() const = 0;
};

}
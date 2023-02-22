#pragma once

#include "logger.hpp"

#include <fstream>

namespace PolymorphicLoggerExample {

class LoggerFile : public Logger {
 public:
  explicit LoggerFile(std::string_view logFilePath);

  void writeMessage(std::string_view) override;

  [[nodiscard]] std::string_view name() const override;
  [[nodiscard]] size_t numberOfRecords() const override;

 private:
  std::ofstream m_file;
  size_t m_numberOfRecords = 0;
};

}  // namespace PolymorphicLoggerExample
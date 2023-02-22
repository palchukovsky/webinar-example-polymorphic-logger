#pragma once

#include "logger.hpp"

#include <fstream>
#include <memory>
#include <vector>

namespace PolymorphicLoggerExample {

class LoggerAggregator : public Logger {
 public:
  void writeMessage(std::string_view) override;

  [[nodiscard]] std::string_view name() const override;
  [[nodiscard]] size_t numberOfRecords() const override;

  void addLogger(std::unique_ptr<Logger>);

 private:
  std::vector<std::shared_ptr<Logger>> m_loggers;
  std::string m_name;
};

}  // namespace PolymorphicLoggerExample
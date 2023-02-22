#include "logger_aggregator.hpp"

#include <iostream>

using namespace PolymorphicLoggerExample;

void LoggerAggregator::addLogger(std::unique_ptr<Logger> newLogger) {
  std::string name = m_name;
  if (!name.empty()) {
    name += " + ";
  }
  name += newLogger->name();

  m_loggers.emplace_back(std::move(newLogger));
  m_name = std::move(name);
}

void LoggerAggregator::writeMessage(const std::string_view message) {
  for (const auto& logger : m_loggers) {
    try {
      logger->writeMessage(message);
    } catch (...) {
      std::cerr << "Field to write log message into logger." << std::endl;
    }
  }
}

std::string_view LoggerAggregator::name() const { return m_name; }

std::size_t LoggerAggregator::numberOfRecords() const {
  size_t result = 0;
  for (const auto& logger : m_loggers) {
    result += logger->numberOfRecords();
  }
  return result;
}

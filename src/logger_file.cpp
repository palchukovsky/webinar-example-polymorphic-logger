#include "logger_file.hpp"

#include <chrono>

using namespace PolymorphicLoggerExample;

LoggerFile::LoggerFile(const std::string_view logFilePath)
    : m_file{logFilePath, std::ios::app} {
  if (!m_file.is_open()) {
    throw std::runtime_error{"Failed to open file for log"};
  }
}

void LoggerFile::writeMessage(const std::string_view message) {
  const auto &now = std::chrono::system_clock::now();
  const auto nowT = std::chrono::system_clock::to_time_t(now);

  m_file << std::put_time(std::localtime(&nowT), "%c") << ": ";
  m_file << message;
  m_file << std::endl;

  ++m_numberOfRecords;
}
std::string_view LoggerFile::name() const { return "File"; }

std::size_t LoggerFile::numberOfRecords() const { return m_numberOfRecords; }

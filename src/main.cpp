
#include "logger_aggregator.hpp"
#include "logger_file.hpp"
#include "logger_udp.hpp"

#include <exception>
#include <iostream>

namespace {

namespace ple = PolymorphicLoggerExample;

auto createLogger() {
  auto result = std::make_unique<ple::LoggerAggregator>();

  result->addLogger(std::make_unique<ple::LoggerFile>("ple.log"));
  result->addLogger(std::make_unique<ple::LoggerUdp>(20917));

  return result;
}

void testLogger() {
  auto logger = createLogger();

  std::cout << "Working with '" << logger->name() << "'..." << std::endl;

  logger->writeMessage("Hello World!");

  logger->writeMessage("Record #1!");

  std::cout << "Entre log message and press Enter...,\n\t...type \"stop\" and "
               "press Enter to stop:"
            << std::endl;
  for (;;) {
    std::string userMessage;
    std::getline(std::cin, userMessage);
    if (userMessage.empty()) {
      continue;
    }
    if (userMessage == "stop") {
      break;
    }

    logger->writeMessage(userMessage);
  }

  logger->writeMessage("Stopping work...");

  std::cout << "Logger collected " << logger->numberOfRecords() << " records."
            << std::endl;
}

}  // namespace

int main() {
  try {
    testLogger();
  } catch (const std::exception &ex) {
    std::cerr << "Fatal error \"" << ex.what() << "\"." << std::endl;
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Fatal UNKNOWN error." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
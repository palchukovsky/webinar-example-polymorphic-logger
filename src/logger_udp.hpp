#pragma once

#include "logger.hpp"

#include <boost/asio.hpp>

#include <fstream>

namespace PolymorphicLoggerExample {

class LoggerUdp : public Logger {
 public:
  using Port = unsigned short;

  explicit LoggerUdp(Port broadcastPort);

  void writeMessage(std::string_view) override;

  [[nodiscard]] std::string_view name() const override;
  [[nodiscard]] size_t numberOfRecords() const override;

 private:
  boost::asio::io_context m_ioContext;
  const boost::asio::ip::udp::endpoint m_endpoint;
  boost::asio::ip::udp::socket m_socket{m_ioContext};

  size_t m_numberOfRecords = 0;
};

}  // namespace PolymorphicLoggerExample
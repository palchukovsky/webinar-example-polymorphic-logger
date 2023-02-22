#include "logger_udp.hpp"

#include <iostream>
#include <strstream>

using namespace PolymorphicLoggerExample;

namespace asio = boost::asio;
namespace ip = asio::ip;

LoggerUdp::LoggerUdp(const Port broadcastPort)
    : m_endpoint(asio::ip::address_v4::broadcast(), broadcastPort) {
  //
  // Preparing socket:
  m_socket.open(ip::udp::v4());
  m_socket.set_option(ip::udp::socket::reuse_address(true));
  m_socket.set_option(asio::socket_base::broadcast(true));
}

void LoggerUdp::writeMessage(const std::string_view message) {
  const auto &now = std::chrono::system_clock::now();
  const auto nowT = std::chrono::system_clock::to_time_t(now);

  std::stringstream buffer;
  buffer << std::put_time(std::localtime(&nowT), "%c") << ": ";
  buffer << message;
  buffer << std::endl;

  m_socket.send_to(asio::buffer(buffer.str()), m_endpoint);

  ++m_numberOfRecords;
}
std::string_view LoggerUdp::name() const { return "UDP"; }

std::size_t LoggerUdp::numberOfRecords() const { return m_numberOfRecords; }

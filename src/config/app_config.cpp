#include "config/app_config.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>

namespace {

constexpr std::uint16_t DEFAULT_SERVER_PORT = 8080;

}

AppConfig AppConfig::from_environment() {
  const char *server_port = std::getenv("SERVER_PORT");

  if (server_port == nullptr) {
    return AppConfig{.server_port = DEFAULT_SERVER_PORT};
  }

  try {
    const int port = std::stoi(server_port);

    if (port < 1 || port > 65535) {
      throw std::out_of_range("SERVER_PORT must be between 1 and 65535");
    }

    return AppConfig{.server_port = static_cast<std::uint16_t>(port)};
  } catch (const std::invalid_argument &) {
    throw std::runtime_error("SERVER_PORT must be a valid integer");
  }
}
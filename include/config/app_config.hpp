#pragma once

#include <cstdint>

struct AppConfig {
  std::uint16_t server_port;

  static AppConfig from_environment();
};
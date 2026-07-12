#pragma once

#include <cstdint>
#include <string>

struct AppConfig {
  std::uint16_t server_port;

  std::string db_host;
  std::uint16_t db_port;
  std::string db_name;
  std::string db_user;
  std::string db_password;

  static AppConfig from_environment();
};
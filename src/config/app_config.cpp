#include "config/app_config.hpp"

#include <cstdlib>
#include <stdexcept>
#include <string>

namespace {

constexpr std::uint16_t DEFAULT_SERVER_PORT = 8080;
constexpr std::uint16_t DEFAULT_DB_PORT = 5432;

std::string get_required_enironment_variable(const char *name) {
  const char *value = std::getenv(name);

  if (value == nullptr || value[0] == '\0') {
    throw std::runtime_error(
        std::string("Required environment variable is missing: ") + name);
  }
  return value;
}

std::uint16_t parse_port(const std::string &value,
                         const std::string &variable_name) {
  try {
    const int port = std::stoi(value);

    if (port < 1 || port > 65535) {
      throw std::out_of_range(variable_name + " must be between 1 and 65535");
    }

    return static_cast<std::uint16_t>(port);
  } catch (const std::invalid_argument &) {
    throw std::runtime_error(variable_name + " must be a valid integer");
  } catch (const std::out_of_range &) {
    throw std::runtime_error(variable_name + " must be between 1 and 65535");
  }
}

} // namespace

AppConfig AppConfig::from_environment() {
  const char *server_port = std::getenv("SERVER_PORT");
  const char *db_port = std::getenv("DB_PORT");

  return AppConfig{
      .server_port = server_port == nullptr
                         ? DEFAULT_SERVER_PORT
                         : parse_port(server_port, "SERVER_PORT"),

      .db_host = get_required_enironment_variable("DB_HOST"),

      .db_port =
          db_port == nullptr ? DEFAULT_DB_PORT : parse_port(db_port, "DB_PORT"),

      .db_name = get_required_enironment_variable("DB_NAME"),
      .db_user = get_required_enironment_variable("DB_USER"),
      .db_password = get_required_enironment_variable("DB_PASSWORD"),
  };
}
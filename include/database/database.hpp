#pragma once

#include "config/app_config.hpp"

#include <pqxx/pqxx>

class Database {
public:
  explicit Database(const AppConfig &config);

  void check_connection();

private:
  pqxx::connection connection_;
};
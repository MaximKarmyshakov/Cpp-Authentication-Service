#include "database/database.hpp"

#include <fmt/format.h>
#include <stdexcept>

Database::Database(const AppConfig &config)
    : connection_(fmt::format("host={} port={} dbname={} user={} password={}",
                              config.db_host, config.db_port, config.db_name,
                              config.db_user, config.db_password)) {}

void Database::check_connection() {
  if (!connection_.is_open()) {
    throw std::runtime_error("Failed to connect to the database");
  }

  pqxx::work transaction(connection_);

  const pqxx::result result = transaction.exec("SELECT 1");

  transaction.commit();

  if (result.empty() || result[0][0].as<int>() != 1) {
    throw std::runtime_error("Database connection check failed");
  }
}

pqxx::connection &Database::connection() { return connection_; }

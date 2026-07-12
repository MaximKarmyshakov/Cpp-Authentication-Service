#pragma once

#include <nlohmann/json.hpp>

#include <optional>
#include <string>

struct RegisterRequest {
  std::string username;
  std::string email;
  std::string phone;
  std::string password;
  std::string role = "individual";

  std::optional<std::string> company_name;
  std::optional<std::string> inn;
  std::optional<nlohmann::json> metadata;
};
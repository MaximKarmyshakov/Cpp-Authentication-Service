#include "auth/register_request_parser.hpp"

RegisterRequest parse_register_request(const nlohmann::json &json) {
  RegisterRequest request;

  request.username = json.at("username").get<std::string>();
  request.email = json.at("email").get<std::string>();
  request.phone = json.at("phone").get<std::string>();
  request.password = json.at("password").get<std::string>();

  if (json.contains("role")) {
    request.role = json.at("role").get<std::string>();
  }

  if (json.contains("company_name")) {
    request.company_name = json.at("company_name").get<std::string>();
  }

  if (json.contains("inn")) {
    request.inn = json.at("inn").get<std::string>();
  }

  if (json.contains("metadata")) {
    request.metadata = json.at("metadata");
  }

  return request;
}
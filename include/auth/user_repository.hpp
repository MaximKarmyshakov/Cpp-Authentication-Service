#pragma once

#include "auth/register_request.hpp"
#include "auth/user.hpp"

#include <pqxx/pqxx>
#include <string>

class UserRepository {
public:
  explicit UserRepository(pqxx::connection &connection);

  User create(const RegisterRequest &request, const std::string &password_hash);

private:
  pqxx::connection &connection_;
};
#include "auth/user_repository.hpp"
#include "auth/user_already_exists_error.hpp"

#include <pqxx/pqxx>
#include <string>

UserRepository::UserRepository(pqxx::connection &connection)
    : connection_(connection) {}

User UserRepository::create(const RegisterRequest &request,
                            const std::string &password_hash) {
  try {
    pqxx::work transaction(connection_);

    const std::optional<std::string> metadata =
        request.metadata.has_value()
            ? std::optional<std::string>(request.metadata->dump())
            : std::nullopt;

    const pqxx::result result = transaction.exec_params(
        R"(
        INSERT INTO users (
          username,
          email,
          phone,
          password_hash,
          role,
          company_name,
          inn,
          metadata
        )
        VALUES (
          $1,
          $2,
          $3,
          $4,
          $5,
          $6,
          $7,
          $8::jsonb
        )
        RETURNING id, username, email, role
      )",
        request.username, request.email, request.phone, password_hash,
        request.role, request.company_name, request.inn, metadata);

    transaction.commit();

    const pqxx::row row = result.one_row();

    return User{.id = row["id"].as<std::string>(),
                .username = row["username"].as<std::string>(),
                .email = row["email"].as<std::string>(),
                .role = row["role"].as<std::string>()};
  } catch (const pqxx::unique_violation &) {
    throw UserAlreadyExistsError(
        "User with this username or email already exists");
  }
}
#include "auth/register_request_validator.hpp"

#include <algorithm>
#include <cctype>
#include <regex>
#include <string>

namespace {

constexpr std::size_t MAX_USERNAME_LENGTH = 64;
constexpr std::size_t MAX_EMAIL_LENGTH = 255;
constexpr std::size_t MAX_PHONE_LENGTH = 32;
constexpr std::size_t MAX_PASSWORD_LENGTH = 20;
constexpr std::size_t MIN_PASSWORD_LENGTH = 8;
constexpr std::size_t MAX_COMPANY_NAME_LENGTH = 256;
constexpr std::size_t MAX_METADATA_SIZE = 4 * 1024;

bool is_valid_email(const std::string &email) {
  static const std::regex email_pattern(
      R"(^[A-Za-z0-9.!#$%&'*+/=?^_`{|}~-]+@[A-Za-z0-9-]+(?:\.[A-Za-z0-9-]+)+$)");
  return std::regex_match(email, email_pattern);
}

bool contains_uppercase(const std::string &str) {
  return std::any_of(str.begin(), str.end(),
                     [](unsigned char c) { return std::isupper(c); });
}

bool contains_lowercase(const std::string &str) {
  return std::any_of(str.begin(), str.end(),
                     [](unsigned char c) { return std::islower(c); });
}

bool contains_digit(const std::string &str) {
  return std::any_of(str.begin(), str.end(),
                     [](unsigned char c) { return std::isdigit(c); });
}

bool is_valid_inn(const std::string &inn) {
  const bool valid_length = (inn.length() == 10 || inn.length() == 12);

  if (!valid_length) {
    return false;
  }

  return std::all_of(inn.begin(), inn.end(),
                     [](unsigned char c) { return std::isdigit(c); });
}

} // namespace

ValidationResult
RegisterRequestValidator::validate(const RegisterRequest &request) {
  ValidationResult result{.valid = true, .errors = {}};

  if (request.username.empty() ||
      request.username.length() > MAX_USERNAME_LENGTH) {
    result.errors.emplace_back(
        "username must contain between 1 and 64 characters");
  }

  if (request.email.empty() || request.email.length() > MAX_EMAIL_LENGTH ||
      !is_valid_email(request.email)) {
    result.errors.emplace_back(
        "email must be a valid email address with at most 255 characters");
  }

  if (request.phone.empty() || request.phone.length() > MAX_PHONE_LENGTH) {
    result.errors.emplace_back(
        "phone is required and must contain at most 32 characters");
  }

  if (request.password.length() < MIN_PASSWORD_LENGTH ||
      request.password.length() > MAX_PASSWORD_LENGTH) {
    result.errors.emplace_back(
        "password must contain between 8 and 20 characters");
  }

  if (!contains_uppercase(request.password)) {
    result.errors.emplace_back(
        "password must contain at least one uppercase letter");
  }

  if (!contains_lowercase(request.password)) {
    result.errors.emplace_back(
        "password must contain at least one lowercase letter");
  }

  if (!contains_digit(request.password)) {
    result.errors.emplace_back("password must contain at least one digit");
  }

  const bool allowed_role = request.role == "individual" ||
                            request.role == "logistics_partner" ||
                            request.role == "business_account";

  if (!allowed_role) {
    result.errors.emplace_back("role is not allowed");
  }

  if (request.role == "business_account") {
    if (!request.company_name.has_value() || request.company_name->empty()) {
      result.errors.emplace_back(
          "company_name is required for business_account");
    }
  }

  if (request.company_name.has_value() &&
      request.company_name->length() > MAX_COMPANY_NAME_LENGTH) {
    result.errors.emplace_back(
        "company_name must contain at most 256 characters");
  }

  if (request.inn.has_value() && !is_valid_inn(*request.inn)) {
    result.errors.emplace_back("inn must contain exactly 10 or 12 digits");
  }

  if (request.metadata.has_value()) {
    if (!request.metadata->is_object()) {
      result.errors.emplace_back("metadata must be a JSON object");
    } else if (request.metadata->dump().size() > MAX_METADATA_SIZE) {
      result.errors.emplace_back("metadata must not exceed 4 KB");
    }
  }

  result.valid = result.errors.empty();

  return result;
}
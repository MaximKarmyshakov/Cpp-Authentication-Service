#include "auth/validation_result.hpp"

#include <algorithm>

bool ValidationResult::has_forbiden_errors() const {
  return std::any_of(errors.begin(), errors.end(),
                     [](const ValidationError &error) {
                       return error.type == ValidationErrorType::Forbidden;
                     });
}
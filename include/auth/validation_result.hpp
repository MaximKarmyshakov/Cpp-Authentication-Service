#pragma once

#include <string>
#include <vector>

enum class ValidationErrorType { Validation, Forbidden };

struct ValidationError {
  ValidationErrorType type;
  std::string message;
};

struct ValidationResult {
  bool valid;
  std::vector<ValidationError> errors;

  bool has_forbiden_errors() const;
};
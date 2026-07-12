#pragma once

#include "auth/register_request.hpp"
#include "auth/validation_result.hpp"

class RegisterRequestValidator {
public:
  static ValidationResult validate(const RegisterRequest &request);
};
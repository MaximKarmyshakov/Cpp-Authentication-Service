#pragma once

#include <stdexcept>
#include <string>

class UserAlreadyExistsError : public std::runtime_error {
public:
  explicit UserAlreadyExistsError(const std::string &message)
      : std::runtime_error(message) {}
};
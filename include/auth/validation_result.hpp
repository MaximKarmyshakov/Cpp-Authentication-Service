#pragma once

#include <string>
#include <vector>

struct ValidationResult {
  bool valid;
  std::vector<std::string> errors;
};
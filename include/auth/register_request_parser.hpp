#pragma once

#include "auth/register_request.hpp"

#include <nlohmann/json.hpp>

RegisterRequest parse_register_request(const nlohmann::json &json);
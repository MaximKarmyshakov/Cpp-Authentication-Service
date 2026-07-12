#include "auth/password_hasher.hpp"

#include <argon2.h>

#include <array>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>

namespace {

constexpr std::uint32_t TIME_COST = 3;
constexpr std::uint32_t MEMORY_COST = 65536;
constexpr std::uint32_t PARALLELISM = 1;

constexpr std::size_t SALT_LENGTH = 16;
constexpr std::size_t HASH_LENGTH = 32;

std::array<std::uint8_t, SALT_LENGTH> generate_salt() {
  std::array<std::uint8_t, SALT_LENGTH> salt{};

  std::random_device random_device;

  for (auto &byte : salt) {
    byte = static_cast<std::uint8_t>(random_device());
  }

  return salt;
}

} // namespace

std::string PasswordHasher::hash(const std::string &password) {
  const auto salt = generate_salt();

  const std::size_t encoded_length = argon2_encodedlen(
      TIME_COST, MEMORY_COST, PARALLELISM, SALT_LENGTH, HASH_LENGTH, Argon2_id);

  std::string encoded_hash(encoded_length, '\0');

  const int result = argon2id_hash_encoded(
      TIME_COST, MEMORY_COST, PARALLELISM, password.data(), password.size(),
      salt.data(), salt.size(), HASH_LENGTH, encoded_hash.data(),
      encoded_hash.size());

  if (result != ARGON2_OK) {
    throw std::runtime_error(std::string("Password hashing failed: ") +
                             argon2_error_message(result));
  }

  encoded_hash.resize(encoded_hash.find('\0'));

  return encoded_hash;
}
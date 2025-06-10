#include "utils/password.hpp"

#include <random>
#include <string>

namespace utils {
namespace password {

std::string generateRandomPassword(int length) {
  const std::string charset =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, charset.length() - 1);

  std::string password;
  password.reserve(length);

  for (int i = 0; i < length; ++i) {
    password += charset[distribution(generator)];
  }

  return password;
}

}  // namespace password
}  // namespace utils
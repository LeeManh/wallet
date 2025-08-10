#include "utils/Validation.hpp"

#include <regex>
#include <string>

namespace utils {
namespace validation {

bool isValidUsername(const std::string& username) {
  std::regex pattern("^[a-zA-Z0-9_]{3,}$");
  return std::regex_match(username, pattern);
}

bool isValidPassword(const std::string& password) {
  return password.length() >= 6 && !password.empty();
}

bool isPositiveNumber(const std::string& number) {
  return std::regex_match(number, std::regex("^[0-9]+$"));
}

bool isPositiveNumber(const int& number) { return number > 0; }

bool isValidEmail(const std::string& email) {
  std::regex pattern(
      R"((\w+)(\.?\w+)*@(\w+\.)+\w{2,})");
  return std::regex_match(email, pattern);
}

}  // namespace validation
}  // namespace utils
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

}  // namespace validation
}  // namespace utils
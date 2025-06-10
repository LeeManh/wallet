#include "utils/validation.hpp"

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

}  // namespace validation
}  // namespace utils

#include "utils/Hash.hpp"

#include <string>

namespace utils {
namespace hash {

std::string generatePasswordHash(const std::string& password) {
  return BCrypt::generateHash(password);
}

bool validatePassword(const std::string& password, const std::string& hash) {
  return BCrypt::validatePassword(password, hash);
}

}  // namespace hash
}  // namespace utils
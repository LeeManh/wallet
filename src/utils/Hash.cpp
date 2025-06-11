#include "utils/Hash.hpp"

#include "libs/Bcrypt.hpp"

namespace utils {
namespace hash {

std::string generatePasswordHash(const std::string& password) {
  return libs::PasswordHash::hashPassword(password);
}

bool validatePassword(const std::string& password, const std::string& hash) {
  return libs::PasswordHash::verifyPassword(password, hash);
}

}  // namespace hash
}  // namespace utils
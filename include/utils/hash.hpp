#ifndef HASH_HPP
#define HASH_HPP

#include <string>

#include "bcrypt/BCrypt.hpp"

namespace utils {
namespace hash {

std::string generatePasswordHash(const std::string& password);

bool validatePassword(const std::string& password,
                      const std::string& hashPassword);
}  // namespace hash
}  // namespace utils

#endif
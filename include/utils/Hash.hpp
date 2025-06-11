#pragma once

#include <string>

#include "libs/Bcrypt.hpp"

namespace utils {
namespace hash {

std::string generatePasswordHash(const std::string& password);
bool validatePassword(const std::string& password, const std::string& hash);

}  // namespace hash
}  // namespace utils
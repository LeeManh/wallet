#pragma once

#include <string>

namespace utils {
namespace password {

// Generate a random password with specified length
std::string generateRandomPassword(int length = 8);

}  // namespace password
}  // namespace utils

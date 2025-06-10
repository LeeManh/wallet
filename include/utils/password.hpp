#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include <string>

namespace utils {
namespace password {

// Generate a random password with specified length
std::string generateRandomPassword(int length = 8);

}  // namespace password
}  // namespace utils

#endif
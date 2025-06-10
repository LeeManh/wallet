#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include <string>

namespace utils {

namespace validation {

bool isValidUsername(const std::string& username);

bool isValidPassword(const std::string& password);

}  // namespace validation
}  // namespace utils

#endif
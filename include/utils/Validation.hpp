#pragma once

#include <string>

namespace utils {

namespace validation {

bool isValidUsername(const std::string& username);

bool isValidPassword(const std::string& password);

bool isPositiveNumber(const std::string& number);
bool isPositiveNumber(const int& number);
bool isValidEmail(const std::string& email);

}  // namespace validation
}  // namespace utils

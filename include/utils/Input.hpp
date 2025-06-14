#pragma once

#include <functional>
#include <string>

#include "utils/Validation.hpp"

namespace utils {
namespace input {

std::string getValidatedInput(
    const std::string& prompt,
    const std::function<bool(const std::string&)>& validator,
    const std::string& errorMessage);

}  // namespace input
}  // namespace utils

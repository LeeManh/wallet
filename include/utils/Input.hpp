#pragma once

#include <functional>
#include <string>
#include <limits>
#include "utils/Validation.hpp"

namespace utils {
namespace input {

std::string getValidatedInput(
    const std::string& prompt,
    const std::function<bool(const std::string&)>& validator,
    const std::string& errorMessage);

std::string getInput(const std::string& prompt);

int getChoice(int min, int max);

void pauseInput();

}  // namespace input
}  // namespace utils

#include "utils/Input.hpp"

#include <iostream>

namespace utils {
namespace input {

std::string getValidatedInput(
    const std::string& prompt,
    const std::function<bool(const std::string&)>& validator,
    const std::string& errorMessage) {
  std::string input;
  do {
    std::cout << prompt;
    std::getline(std::cin, input);

    if (!validator(input)) {
      std::cout << errorMessage << std::endl;
    }
  } while (!validator(input));

  return input;
}

}  // namespace input
}  // namespace utils
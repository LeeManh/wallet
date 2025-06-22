#include "utils/Input.hpp"

#include <iostream>

#include "utils/MessageHandler.hpp"

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

std::string getInput(const std::string& prompt) {
  std::cout << prompt;
  std::string input;
  std::getline(std::cin, input);
  return input;
}

int getChoice(int min, int max) {
  int choice;

  while (true) {
    std::cout << "Nhập lựa chọn: ";

    if (!(std::cin >> choice)) {
      utils::MessageHandler::logError(
          "Lựa chọn không hợp lệ! Vui lòng nhập một số.");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (choice < min || choice > max) {
      utils::MessageHandler::logError(
          "Lựa chọn không hợp lệ! Vui lòng nhập số từ " + std::to_string(min) +
          " đến " + std::to_string(max) + ".");
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return choice;
    }
  }
}

void pauseInput() {
  utils::MessageHandler::logMessage("\nNhấn Enter để tiếp tục...");
  std::cin.ignore();
  std::cin.get();
}

}  // namespace input
}  // namespace utils
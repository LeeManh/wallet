#include "views/View.hpp"

#include <iostream>
#include <limits>

#include "utils/MessageHandler.hpp"

namespace views {

std::string View::getInput(const std::string& prompt) {
  std::cout << prompt;
  std::string input;
  std::getline(std::cin, input);
  return input;
}

int View::getChoice(int min, int max) {
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

}  // namespace views
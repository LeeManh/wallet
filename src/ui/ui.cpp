#include "ui/ui.hpp"

#include <iostream>
#include <limits>
#include <string>

#include "auth/auth.hpp"
#include "utils/input.hpp"
#include "utils/validation.hpp"

namespace ui {
void UserInterface::displayMainMenu() {
  std::cout << "\n=== Hệ thống quản lý ví điểm thưởng ===" << std::endl;
  std::cout << "1. Đăng nhập" << std::endl;
  std::cout << "2. Đăng ký" << std::endl;
  std::cout << "3. Thoát" << std::endl;
  std::cout << "Nhập lựa chọn (1-3): ";
}

int UserInterface::getMenuChoice() {
  int choice;
  while (!(std::cin >> choice) || choice < 1 || choice > 3) {
    std::cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại (1-3): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n');  // Clear the newline
  return choice;
}

std::string UserInterface::getInput(const std::string& prompt) {
  std::string input;
  std::cout << prompt;
  getline(std::cin, input);
  return input;
}

bool UserInterface::handleRegistration() {
  std::cout << "\n=== Đăng ký tài khoản ===" << std::endl;

  // Nhập username
  std::string username = utils::input::getValidatedInput(
      "Nhập tên đăng nhập: ", utils::validation::isValidUsername,
      "- Tên đăng nhập không hợp lệ.\n"
      "- Tên đăng nhập phải có ít nhất 3 ký tự và chỉ chứa chữ cái, số và "
      "dấu "
      "gạch dưới");

  // Nhập password
  std::string password = utils::input::getValidatedInput(
      "Nhập mật khẩu: ", utils::validation::isValidPassword,
      "- Mật khẩu không hợp lệ.\n"
      "- Mật khẩu phải có ít nhất 6 ký tự và không được trống.");

  // Nhập lại password
  std::string confirmPassword;
  do {
    confirmPassword = getInput("Nhập lại mật khẩu: ");
    if (password != confirmPassword) {
      std::cout << "Mật khẩu không khớp. Vui lòng nhập lại." << std::endl;
    }
  } while (password != confirmPassword);

  // Nhập họ tên
  std::string fullName = getInput("Nhập họ và tên: ");

  return auth::registerUser(username, password, fullName);
}

bool UserInterface::handleLogin() {
  std::cout << "\n=== Đăng nhập ===" << std::endl;

  // Nhập username
  std::string username = utils::input::getValidatedInput(
      "Nhập tên đăng nhập: ", utils::validation::isValidUsername,
      "- Tên đăng nhập không hợp lệ.\n"
      "- Tên đăng nhập phải có ít nhất 3 ký tự và chỉ chứa chữ cái, số và "
      "dấu "
      "gạch dưới");

  // Nhập password
  std::string password = utils::input::getValidatedInput(
      "Nhập mật khẩu: ", utils::validation::isValidPassword,
      "- Mật khẩu không hợp lệ.\n"
      "- Mật khẩu phải có ít nhất 6 ký tự và không được trống.");

  return auth::login(username, password);
}

}  // namespace ui
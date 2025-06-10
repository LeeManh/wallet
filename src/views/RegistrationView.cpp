#include "views/RegistrationView.hpp"

#include <iostream>
#include <limits>

#include "controllers/AuthController.hpp"

namespace views {

void RegistrationView::display() {
  std::cout << "\n=== Đăng ký tài khoản ===" << std::endl;
}

int RegistrationView::getChoice() {
  return 0;  // Không cần xử lý choice cho view này
}

void RegistrationView::handleRegistration() {
  std::string username = getInput("Nhập tên đăng nhập: ");
  std::string password = getInput("Nhập mật khẩu: ");
  std::string confirmPassword = getInput("Nhập lại mật khẩu: ");
  std::string fullName = getInput("Nhập họ và tên: ");

  if (password != confirmPassword) {
    std::cout << "Mật khẩu không khớp!" << std::endl;
    return;
  }

  controllers::AuthController authController;
  authController.registerUser(username, password, fullName);
}

}  // namespace views
#include "views/RegistrationView.hpp"

#include "controllers/AuthController.hpp"
#include "utils/MessageHandler.hpp"

namespace views {

void RegistrationView::display() {
  utils::MessageHandler::logMessage("\n=== Đăng ký tài khoản ===");

  std::string username = getInput("Nhập tên đăng nhập: ");
  std::string password = getInput("Nhập mật khẩu: ");
  std::string confirmPassword = getInput("Nhập lại mật khẩu: ");

  if (password != confirmPassword) {
    utils::MessageHandler::logError("Mật khẩu không khớp!");
    return;
  }

  std::string email = getInput("Nhập email: ");
  std::string fullName = getInput("Nhập họ tên đầy đủ: ");

  controllers::AuthController authController;
  if (authController.registerUser(username, password, email, fullName)) {
    utils::MessageHandler::logSuccess("Đăng ký tài khoản thành công!");
  }
}

}  // namespace views
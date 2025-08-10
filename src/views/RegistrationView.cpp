#include "views/RegistrationView.hpp"

#include "controllers/AuthController.hpp"
#include "exceptions/Exception.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"

namespace views {

void RegistrationView::display() {
  utils::MessageHandler::logMessage("");
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│             ĐĂNG KÝ TÀI KHOẢN               │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  std::string username;
  while (true) {
    username = utils::input::getInput("Nhập tên đăng nhập: ");
    if (!utils::validation::isValidUsername(username)) {
    utils::MessageHandler::logError(
        "Tên đăng nhập không hợp lệ! Tối thiểu 3 ký tự, chỉ gồm chữ, số, dấu "
        "gạch dưới.");
    } else {
    break;
    }
  }

  std::string password;
  while (true) {
    password = utils::input::getInput("Nhập mật khẩu: ");
    if (!utils::validation::isValidPassword(password)) {
    utils::MessageHandler::logError("Mật khẩu không hợp lệ! Tối thiểu 6 ký tự.");
    } else {
    break;
    }
  }

  std::string confirmPassword;
  while (true) {
    confirmPassword = utils::input::getInput("Nhập lại mật khẩu: ");
    if (password != confirmPassword) {
    utils::MessageHandler::logError("Mật khẩu không khớp!");
    } else {
    break;
    } 
  }

  std::string email;
  while (true) {
    email = utils::input::getInput("Nhập email: ");
    if (!utils::validation::isValidEmail(email)) {
    utils::MessageHandler::logError("Email không hợp lệ!");
    } else {
    break;
    }
  }

  std::string fullName;
  while (true) {
    fullName = utils::input::getInput("Nhập họ tên đầy đủ: ");
    if (fullName.empty()) {
    utils::MessageHandler::logError("Họ tên không được để trống!");
    } else {
    break;
    }
  }

  controllers::AuthController::registerUser(username, password, email,
                                            fullName);
}

}  // namespace views
#include "views/RegistrationView.hpp"

#include "controllers/AuthController.hpp"
#include "exceptions/Exception.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"

namespace views {

void RegistrationView::display() {
  utils::MessageHandler::logMessage("\n=== Đăng ký tài khoản ===");

  std::string username = utils::input::getInput("Nhập tên đăng nhập: ");
  std::string password = utils::input::getInput("Nhập mật khẩu: ");
  std::string confirmPassword = utils::input::getInput("Nhập lại mật khẩu: ");

  if (password != confirmPassword)
    throw exceptions::ValidationException("Mật khẩu không khớp!");

  std::string email = utils::input::getInput("Nhập email: ");
  std::string fullName = utils::input::getInput("Nhập họ tên đầy đủ: ");

  controllers::AuthController::registerUser(username, password, email,
                                            fullName);
}

}  // namespace views
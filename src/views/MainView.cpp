#include "views/MainView.hpp"

#include "controllers/AuthController.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"
#include "views/AdminView.hpp"
#include "views/CustomerView.hpp"
#include "views/RegistrationView.hpp"

namespace views {

void MainView::display() {
  while (true) {
    utils::MessageHandler::logMessage(
        "\n=== Hệ thống quản lý ví điểm thưởng ===");
    utils::MessageHandler::logMessage("[1] Đăng nhập");
    utils::MessageHandler::logMessage("[2] Đăng ký");
    utils::MessageHandler::logMessage("[0] Thoát");

    int choice = utils::input::getChoice(0, 2);

    switch (choice) {
      case 1:
        handleLogin();
        break;
      case 2:
        handleRegistration();
        break;
      case 0:
        utils::MessageHandler::logSuccess(
            "Cảm ơn bạn đã sử dụng chương trình!");
        return;
    }
  }
}

void MainView::handleLogin() {
  utils::MessageHandler::logMessage("\n=== Đăng nhập ===");
  std::string username = utils::input::getInput("Nhập tên đăng nhập: ");
  std::string password = utils::input::getInput("Nhập mật khẩu: ");

  auto [success, userId, isAdmin] =
      controllers::AuthController::login(username, password);

  if (!success) return;

  if (isAdmin) {
    views::AdminView adminView;
    adminView.userId = userId;
    adminView.display();
  } else {
    views::CustomerView customerView;
    customerView.userId = userId;
    customerView.display();
  }
}

void MainView::handleRegistration() {
  views::RegistrationView registrationView;
  registrationView.display();
}

}  // namespace views
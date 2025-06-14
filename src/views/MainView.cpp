#include "views/MainView.hpp"

#include "controllers/MenuController.hpp"
#include "utils/MessageHandler.hpp"

namespace views {

void MainView::display() {
  while (true) {
    utils::MessageHandler::logMessage(
        "\n=== Hệ thống quản lý ví điểm thưởng ===");
    utils::MessageHandler::logMessage("[1] Đăng nhập");
    utils::MessageHandler::logMessage("[2] Đăng ký");
    utils::MessageHandler::logMessage("[0] Thoát");

    int choice = getChoice(0, 2);

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
  std::string username = getInput("Nhập tên đăng nhập: ");
  std::string password = getInput("Nhập mật khẩu: ");

  controllers::MenuController menuController;
  menuController.handleLogin(username, password);
}

void MainView::handleRegistration() {
  controllers::MenuController menuController;
  menuController.handleRegistration();
}

}  // namespace views
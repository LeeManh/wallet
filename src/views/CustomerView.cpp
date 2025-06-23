#include "views/CustomerView.hpp"

#include "controllers/AuthController.hpp"
#include "controllers/TransactionController.hpp"
#include "controllers/WalletController.hpp"
#include "utils/Format.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"
namespace views {

void CustomerView::display() {
  while (true) {
    utils::MessageHandler::logMessage("\n=== MENU KHÁCH HÀNG ===");
    utils::MessageHandler::logMessage("[1] Xem số dư");
    utils::MessageHandler::logMessage("[2] Chuyển điểm");
    utils::MessageHandler::logMessage("[3] Xem lịch sử giao dịch");
    utils::MessageHandler::logMessage("[4] Điều chỉnh thông tin cá nhân");
    utils::MessageHandler::logMessage("[5] Đổi mật khẩu");
    utils::MessageHandler::logMessage("[0] Đăng xuất");

    int choice = utils::input::getChoice(0, 5);

    switch (choice) {
      case 1:
        handleViewBalance();
        break;
      case 2:
        handleTransferPoints();
        break;
      case 3:
        handleViewTransactionHistory();
        break;
      case 4:
        handleEditProfile();
        break;
      case 5:
        handleChangePassword();
        break;
      case 0:
        return;
    }
  }
}

void CustomerView::handleViewBalance() {
  utils::MessageHandler::logMessage("\n=== XEM SỐ DƯ ĐIỂM ===");

  controllers::WalletController::getWalletByUserId(userId);

  utils::MessageHandler::logMessage("\nNhấn Enter để tiếp tục...");
  std::cin.get();
}

void CustomerView::handleTransferPoints() {
  std::string toUserId = utils::input::getInput("Nhập id người nhận nhận: ");
  if (!utils::validation::isPositiveNumber(toUserId)) {
    utils::MessageHandler::logError("ID người nhận không hợp lệ!");
    return;
  }

  std::string points = utils::input::getInput("Nhập số điểm cần chuyển: ");
  if (!utils::validation::isPositiveNumber(points)) {
    utils::MessageHandler::logError("Số điểm không hợp lệ!");
    return;
  }

  controllers::TransactionController::transferPoints(
      userId, std::stoi(toUserId), std::stod(points));
}

void CustomerView::handleViewTransactionHistory() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void CustomerView::handleEditProfile() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void CustomerView::handleChangePassword() {
  utils::MessageHandler::logMessage("\n=== ĐỔI MẬT KHẨU ===");

  std::string currentPassword =
      utils::input::getInput("Nhập mật khẩu hiện tại: ");
  std::string newPassword = utils::input::getInput("Nhập mật khẩu mới: ");
  std::string confirmPassword =
      utils::input::getInput("Nhập lại mật khẩu mới: ");

  if (newPassword != confirmPassword) {
    utils::MessageHandler::logError("Mật khẩu mới không khớp!");
    return;
  }

  controllers::AuthController::changePasswordWithOTP(userId, currentPassword,
                                                     newPassword);

  utils::input::pauseInput();
}

}  // namespace views
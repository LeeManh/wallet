#include "views/CustomerView.hpp"

#include "controllers/AuthController.hpp"
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

    int choice = getChoice(0, 5);

    switch (choice) {
      case 1:
        handleViewBalance();
        break;
      case 2:
        handleTransfer();
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

  try {
    controllers::WalletController walletController;
    models::Wallet wallet = walletController.getWalletByUserId(userId);
    utils::MessageHandler::logMessage(
        "Số dư điểm hiện tại của bạn: " +
        utils::format::formatPoint(wallet.getPoint()) + " điểm");
  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Không thể lấy thông tin số dư!");
  }

  utils::MessageHandler::logMessage("\nNhấn Enter để tiếp tục...");
  std::cin.get();
}

void CustomerView::handleTransfer() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void CustomerView::handleViewTransactionHistory() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void CustomerView::handleEditProfile() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void CustomerView::handleChangePassword() {
  utils::MessageHandler::logMessage("\n=== ĐỔI MẬT KHẨU ===");

  std::string currentPassword = getInput("Nhập mật khẩu hiện tại: ");
  std::string newPassword = getInput("Nhập mật khẩu mới: ");
  std::string confirmPassword = getInput("Nhập lại mật khẩu mới: ");

  if (newPassword != confirmPassword) {
    utils::MessageHandler::logError("Mật khẩu mới không khớp!");
    return;
  }

  utils::MessageHandler::logMessage("\nGửi mã OTP để xác thực...");

  controllers::AuthController authController;
  bool otpSent = authController.sendOTPInfoChange(userId);

  if (!otpSent) {
    utils::MessageHandler::logError("Không thể gửi mã OTP. Vui lòng thử lại!");
    return;
  }

  std::string otp = getInput("Nhập mã OTP: ");

  bool success = authController.verifyOTPAndChangePassword(
      userId, otp, currentPassword, newPassword);

  if (success) {
    utils::MessageHandler::logSuccess("Đổi mật khẩu thành công!");
  } else {
    utils::MessageHandler::logError(
        "Đổi mật khẩu thất bại. Vui lòng kiểm tra lại thông tin!");
  }
}

}  // namespace views
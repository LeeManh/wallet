#include "views/AdminView.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "controllers/AuthController.hpp"
#include "controllers/WalletController.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"

namespace views {

void AdminView::display() {
  while (true) {
    utils::MessageHandler::logMessage("\n=== MENU QUẢN TRỊ VIÊN ===");
    utils::MessageHandler::logMessage("[1] Xem danh sách người dùng");
    utils::MessageHandler::logMessage("[2] Xem danh sách ví");
    utils::MessageHandler::logMessage("[3] Xem lịch sử giao dịch");
    utils::MessageHandler::logMessage("[4] Tạo tài khoản mới cho người dùng");
    utils::MessageHandler::logMessage("[5] Điều chỉnh thông tin người dùng");
    utils::MessageHandler::logMessage("[6] Xem số dư ví tổng");
    utils::MessageHandler::logMessage("[7] Đổi mật khẩu");
    utils::MessageHandler::logMessage("[0] Đăng xuất");

    int choice = getChoice(0, 7);

    switch (choice) {
      case 1:
        handleViewAllUsers();
        break;
      case 2:
        handleViewAllWallets();
        break;
      case 3:
        handleViewTransactionHistory();
        break;
      case 4:
        handleCreateAccount();
        break;
      case 5:
        handleEditUserInfo();
        break;
      case 6:
        handleManageTotalWallet();
        break;
      case 7:
        handleChangePassword();
        break;
      case 0:
        return;
    }
  }
}

void AdminView::handleCreateAccount() {
  utils::MessageHandler::logMessage(
      "\n=== TẠO TÀI KHOẢN MỚI CHO NGƯỜI DÙNG ===");

  std::string username = getInput("Nhập tên đăng nhập: ");
  std::string email = getInput("Nhập email: ");
  std::string fullName = getInput("Nhập họ tên đầy đủ: ");

  std::string generatedPassword;

  controllers::AuthController::registerUserByAdmin(username, email, fullName,
                                                   generatedPassword);
}

void AdminView::handleViewAllUsers() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void AdminView::handleViewAllWallets() {
  utils::MessageHandler::logMessage(
      "\n=== DANH SÁCH TẤT CẢ VÍ TRONG HỆ THỐNG ===");

  controllers::WalletController::printListWallet();

  utils::MessageHandler::logMessage("\nNhấn Enter để tiếp tục...");
  std::cin.ignore();
  std::cin.get();
}

void AdminView::handleViewTransactionHistory() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void AdminView::handleEditUserInfo() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void AdminView::handleManageTotalWallet() {
  utils::MessageHandler::logMessage("\n=== XEM SỐ DƯ VÍ HỆ THỐNG ===");

  controllers::WalletController::getSystemWallet();

  utils::MessageHandler::logMessage("\nNhấn Enter để tiếp tục...");
  std::cin.ignore();
  std::cin.get();
}

void AdminView::handleChangePassword() {
  utils::MessageHandler::logMessage("\n=== ĐỔI MẬT KHẨU ===");

  std::string currentPassword = getInput("Nhập mật khẩu hiện tại: ");
  std::string newPassword = getInput("Nhập mật khẩu mới: ");
  std::string confirmPassword = getInput("Nhập lại mật khẩu mới: ");

  if (newPassword != confirmPassword) {
    utils::MessageHandler::logError("Mật khẩu mới không khớp!");
    return;
  }

    utils::MessageHandler::logMessage("\nGửi mã OTP để xác thực...");
  controllers::AuthController::sendOTPInfoChange(userId);

  std::string otpCode = getInput("Nhập mã OTP đã được gửi: ");
  controllers::AuthController::verifyOTPAndChangePassword(
      userId, otpCode, currentPassword, newPassword);
}

}  // namespace views
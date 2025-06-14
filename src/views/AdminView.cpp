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

  controllers::AuthController authController;
  std::string generatedPassword;

  if (authController.registerUserByAdmin(username, email, fullName,
                                         generatedPassword)) {
    utils::MessageHandler::logSuccess("\nTạo tài khoản thành công!");
    utils::MessageHandler::logMessage("Tên đăng nhập: " + username);
    utils::MessageHandler::logMessage("Email: " + email);
    utils::MessageHandler::logMessage("Mật khẩu: " + generatedPassword);
    utils::MessageHandler::logMessage(
        "Vui lòng lưu lại mật khẩu này để đăng nhập lần đầu!");
  }
}

void AdminView::handleViewAllUsers() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void AdminView::handleViewAllWallets() {
  utils::MessageHandler::logMessage(
      "\n=== DANH SÁCH TẤT CẢ VÍ TRONG HỆ THỐNG ===");

  controllers::WalletController walletController;
  auto wallets = walletController.getAllWallets();

  if (wallets.empty()) {
    utils::MessageHandler::logWarning("Không có ví nào trong hệ thống!");
  } else {
    utils::MessageHandler::logMessage("");

    int count = 1;
    for (const auto& wallet : wallets) {
      char createdStr[20];
      struct tm* timeinfo;

      time_t createdAt = wallet.getCreatedAt();
      timeinfo = localtime(&createdAt);
      strftime(createdStr, sizeof(createdStr), "%d/%m/%Y %H:%M", timeinfo);

      std::string walletTypeStr =
          (wallet.getWalletType() == models::WalletType::SYSTEM) ? "SYSTEM"
                                                                 : "USER";

      utils::MessageHandler::logMessage(
          "[" + std::to_string(count) +
          "] Ví ID: " + std::to_string(wallet.getId()) +
          " | User: " + std::to_string(wallet.getUserId()) + " | Số điểm: " +
          utils::format::formatPoint(wallet.getPoint()) + " điểm" +
          " | Loại: " + walletTypeStr + " | Tạo: " + std::string(createdStr));
      count++;
    }

    utils::MessageHandler::logMessage(std::string(60, '-'));
    utils::MessageHandler::logMessage("Tổng số ví: " +
                                      std::to_string(wallets.size()));

    double totalPoint = 0;
    int userWallets = 0;
    int systemWallets = 0;

    for (const auto& wallet : wallets) {
      totalPoint += wallet.getPoint();
      if (wallet.getWalletType() == models::WalletType::SYSTEM) {
        systemWallets++;
      } else {
        userWallets++;
      }
    }

    utils::MessageHandler::logMessage(
        "Tổng số điểm hệ thống: " + utils::format::formatPoint(totalPoint) +
        " điểm");
    utils::MessageHandler::logMessage(
        "Ví người dùng: " + std::to_string(userWallets) +
        " | Ví hệ thống: " + std::to_string(systemWallets));
  }

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

  controllers::WalletController walletController;
  auto systemWallet = walletController.getSystemWallet();

  if (systemWallet.getId() != -1) {
    utils::MessageHandler::logMessage(
        "Số dư ví hệ thống hiện tại: " +
        utils::format::formatPoint(systemWallet.getPoint()) + " điểm");
  } else {
    utils::MessageHandler::logError(
        "Không tìm thấy ví hệ thống hoặc có lỗi xảy ra!");
    utils::MessageHandler::logMessage(
        "Vui lòng kiểm tra lại cấu hình hệ thống.");
  }

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

  controllers::AuthController authController;

  utils::MessageHandler::logMessage("\nGửi mã OTP để xác thực...");
  if (!authController.sendOTPInfoChange(userId)) {
    utils::MessageHandler::logError("Không thể gửi mã OTP. Vui lòng thử lại!");
    return;
  }

  std::string otpCode = getInput("Nhập mã OTP đã được gửi: ");

  if (authController.verifyOTPAndChangePassword(userId, otpCode,
                                                currentPassword, newPassword)) {
    utils::MessageHandler::logSuccess("Đổi mật khẩu thành công!");
  } else {
    utils::MessageHandler::logError(
        "Đổi mật khẩu thất bại. Vui lòng kiểm tra lại thông tin!");
  }
}

}  // namespace views
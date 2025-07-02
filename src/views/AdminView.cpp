#include "views/AdminView.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "controllers/AuthController.hpp"
#include "controllers/TransactionController.hpp"
#include "controllers/WalletController.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"

namespace views {

void AdminView::display() {
  while (true) {
    utils::MessageHandler::logMessage(
        "┌─────────────────────────────────────────────┐");
    utils::MessageHandler::logMessage(
        "│              MENU QUẢN TRỊ VIÊN             │");
    utils::MessageHandler::logMessage(
        "├─────────────────────────────────────────────┤");
    utils::MessageHandler::logMessage(
        "│ [1] Xem danh sách người dùng                │");
    utils::MessageHandler::logMessage(
        "│ [2] Xem danh sách ví                        │");
    utils::MessageHandler::logMessage(
        "│ [3] Xem lịch sử giao dịch                   │");
    utils::MessageHandler::logMessage(
        "│ [4] Tạo tài khoản mới cho người dùng        │");
    utils::MessageHandler::logMessage(
        "│ [5] Điều chỉnh thông tin người dùng         │");
    utils::MessageHandler::logMessage(
        "│ [6] Xem số dư ví tổng                       │");
    utils::MessageHandler::logMessage(
        "│ [7] Đổi mật khẩu                            │");
    utils::MessageHandler::logMessage(
        "│ [8] Chuyển điểm                             │");
    utils::MessageHandler::logMessage(
        "│ [0] Đăng xuất                               │");
    utils::MessageHandler::logMessage(
        "└─────────────────────────────────────────────┘");

    int choice = utils::input::getChoice(0, 8);

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
      case 8:
        handleTransferPoints();
        break;
      case 0:
        return;
    }
  }
}

void AdminView::handleCreateAccount() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│         TẠO TÀI KHOẢN MỚI CHO NGƯỜI DÙNG    │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  std::string username = utils::input::getInput("Nhập tên đăng nhập: ");
  std::string email = utils::input::getInput("Nhập email: ");
  std::string fullName = utils::input::getInput("Nhập họ tên đầy đủ: ");

  std::string generatedPassword;

  controllers::AuthController::registerUserByAdmin(username, email, fullName,
                                                   generatedPassword);
}

void AdminView::handleViewAllUsers() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│         DANH SÁCH TẤT CẢ NGƯỜI DÙNG         │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  controllers::AuthController::printListUsers();

  utils::input::pauseInput();
}

void AdminView::handleViewAllWallets() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│      DANH SÁCH TẤT CẢ VÍ TRONG HỆ THỐNG     │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  controllers::WalletController::printListWallet();

  utils::input::pauseInput();
}

void AdminView::handleViewTransactionHistory() {
  utils::MessageHandler::logMessage("Chức năng đang được phát triển...");
}

void AdminView::handleEditUserInfo() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│         ĐIỀU CHỈNH THÔNG TIN NGƯỜI DÙNG     │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  std::string userIdStr = utils::input::getInput("Nhập ID người dùng cần chỉnh sửa: ");
  if (!utils::validation::isPositiveNumber(userIdStr)) {
    utils::MessageHandler::logError("ID người dùng không hợp lệ!");
    return;
  }
  int userId = std::stoi(userIdStr);

  std::string newFullName = utils::input::getInput("Nhập họ tên mới (bỏ trống nếu không đổi): ");
  std::string newEmail = utils::input::getInput("Nhập email mới (bỏ trống nếu không đổi): ");

  if (newFullName.empty() && newEmail.empty()) {
    utils::MessageHandler::logMessage("Không có thông tin nào được thay đổi.");
    return;
  }

  controllers::AuthController::editUserInfoByAdmin(userId, newFullName, newEmail);

  utils::input::pauseInput();
}

void AdminView::handleManageTotalWallet() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│              XEM SỐ DƯ VÍ HỆ THỐNG          │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  controllers::WalletController::getSystemWallet();

  utils::input::pauseInput();
}

void AdminView::handleChangePassword() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│                 ĐỔI MẬT KHẨU                │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

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

void AdminView::handleTransferPoints() {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│                CHUYỂN ĐIỂM                  │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

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

}  // namespace views
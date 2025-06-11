#include "views/AdminView.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "controllers/AuthController.hpp"
#include "controllers/WalletController.hpp"

namespace views {

void AdminView::display() {
  std::cout << "\n=== MENU QUẢN TRỊ VIÊN ===" << std::endl;
  std::cout << "[1] Xem danh sách người dùng" << std::endl;
  std::cout << "[2] Xem danh sách ví" << std::endl;
  std::cout << "[3] Xem lịch sử giao dịch" << std::endl;
  std::cout << "[4] Tạo tài khoản mới cho người dùng" << std::endl;
  std::cout << "[5] Điều chỉnh thông tin người dùng" << std::endl;
  std::cout << "[6] Xem số dư ví tổng" << std::endl;
  std::cout << "[7] Đổi mật khẩu" << std::endl;
  std::cout << "[0] Đăng xuất" << std::endl;
  std::cout << "Nhập lựa chọn: ";
}

int AdminView::getChoice() {
  int choice;
  while (!(std::cin >> choice) || choice < 0 || choice > 7) {
    std::cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại (0-7): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return choice;
}

void AdminView::handleCreateAccount() {
  std::cout << "\n=== TẠO TÀI KHOẢN MỚI CHO NGƯỜI DÙNG ===" << std::endl;

  std::string username = getInput("Nhập tên đăng nhập: ");
  std::string email = getInput("Nhập email: ");
  std::string fullName = getInput("Nhập họ và tên: ");

  controllers::AuthController authController;
  std::string generatedPassword;

  if (authController.createUserByAdmin(username, email, fullName,
                                       generatedPassword)) {
    std::cout << "\nTạo tài khoản thành công!" << std::endl;
    std::cout << "Tên đăng nhập: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Mật khẩu: " << generatedPassword << std::endl;
    std::cout << "Vui lòng lưu lại mật khẩu này để đăng nhập lần đầu!"
              << std::endl;
  }
}

void AdminView::handleViewAllUsers() {
  // TODO: Gọi UserController để lấy danh sách người dùng
  std::cout << "Chức năng đang được phát triển..." << std::endl;
}

void AdminView::handleViewAllWallets() {
  std::cout << "\n=== DANH SÁCH TẤT CẢ VÍ TRONG HỆ THỐNG ===" << std::endl;

  auto wallets = controllers::WalletController::getAllWallets();

  if (wallets.empty()) {
    std::cout << "Không có ví nào trong hệ thống!" << std::endl;
  } else {
    std::cout << std::endl;

    // Hiển thị từng ví theo format list
    int count = 1;
    for (const auto& wallet : wallets) {
      // Format thời gian
      char createdStr[20];
      struct tm* timeinfo;

      time_t createdAt = wallet.getCreatedAt();
      timeinfo = localtime(&createdAt);
      strftime(createdStr, sizeof(createdStr), "%d/%m/%Y %H:%M", timeinfo);

      // Loại ví
      std::string walletTypeStr =
          (wallet.getWalletType() == models::WalletType::SYSTEM) ? "SYSTEM"
                                                                 : "USER";

      // Hiển thị thông tin ví
      std::cout << "[" << count << "] Ví ID: " << wallet.getId()
                << " | User: " << wallet.getUserId()
                << " | Số điểm: " << std::fixed << std::setprecision(2)
                << wallet.getPoint() << " điểm"
                << " | Loại: " << walletTypeStr << " | Tạo: " << createdStr
                << std::endl;
      count++;
    }

    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Tổng số ví: " << wallets.size() << std::endl;

    // Tính tổng số dư
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

    std::cout << "Tổng số điểm hệ thống: " << std::fixed << std::setprecision(2)
              << totalPoint << " điểm" << std::endl;
    std::cout << "Ví người dùng: " << userWallets
              << " | Ví hệ thống: " << systemWallets << std::endl;
  }

  std::cout << "\nNhấn Enter để tiếp tục...";
  std::cin.ignore();
  std::cin.get();
}

void AdminView::handleViewTransactionHistory() {
  // TODO: Gọi TransactionController để lấy lịch sử giao dịch
  std::cout << "Chức năng đang được phát triển..." << std::endl;
}

void AdminView::handleEditUserInfo() {
  // TODO: Gọi UserController để điều chỉnh thông tin người dùng
  std::cout << "Chức năng đang được phát triển..." << std::endl;
}

void AdminView::handleManageTotalWallet() {
  std::cout << "\n=== XEM SỐ DƯ VÍ HỆ THỐNG ===" << std::endl;

  int walletId;
  double point;

  // Gọi WalletController để lấy thông tin ví hệ thống
  if (controllers::WalletController::getSystemWallet(walletId, point)) {
    std::cout << "Số dư ví hệ thống hiện tại: " << point << " điểm"
              << std::endl;
  } else {
    std::cout << "Không tìm thấy ví hệ thống hoặc có lỗi xảy ra!" << std::endl;
    std::cout << "Vui lòng kiểm tra lại cấu hình hệ thống." << std::endl;
  }

  std::cout << "\nNhấn Enter để tiếp tục...";
  std::cin.ignore();
  std::cin.get();
}

void AdminView::handleChangePassword() {
  std::cout << "\n=== ĐỔI MẬT KHẨU ===" << std::endl;

  std::string currentPassword = getInput("Nhập mật khẩu hiện tại: ");
  std::string newPassword = getInput("Nhập mật khẩu mới: ");
  std::string confirmPassword = getInput("Nhập lại mật khẩu mới: ");

  if (newPassword != confirmPassword) {
    std::cout << "Mật khẩu mới không khớp!" << std::endl;
    return;
  }

  // Gửi OTP trước khi đổi mật khẩu
  controllers::AuthController authController;

  std::cout << "\nGửi mã OTP để xác thực..." << std::endl;
  if (!authController.sendOTPInfoChange(userId)) {
    std::cout << "Không thể gửi mã OTP. Vui lòng thử lại!" << std::endl;
    return;
  }

  // Nhập mã OTP từ người dùng
  std::string otpCode = getInput("\nNhập mã OTP đã được gửi: ");

  // Thực hiện đổi mật khẩu với xác thực OTP
  if (authController.verifyOTPAndChangePassword(userId, otpCode,
                                                currentPassword, newPassword)) {
    std::cout << "Đổi mật khẩu thành công!" << std::endl;
  } else {
    std::cout << "Đổi mật khẩu thất bại. Vui lòng kiểm tra lại thông tin!"
              << std::endl;
  }
}

}  // namespace views
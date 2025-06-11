#include "views/CustomerView.hpp"

#include <iostream>
#include <limits>

#include "controllers/AuthController.hpp"
#include "controllers/WalletController.hpp"

namespace views {

void CustomerView::display() {
  std::cout << "\n=== MENU KHÁCH HÀNG ===" << std::endl;
  std::cout << "[1] Xem số dư" << std::endl;
  std::cout << "[2] Chuyển điểm" << std::endl;
  std::cout << "[3] Xem lịch sử giao dịch" << std::endl;
  std::cout << "[4] Điều chỉnh thông tin cá nhân" << std::endl;
  std::cout << "[5] Đổi mật khẩu" << std::endl;
  std::cout << "[0] Đăng xuất" << std::endl;
  std::cout << "Nhập lựa chọn: ";
}

int CustomerView::getChoice() {
  int choice;
  while (!(std::cin >> choice) || choice < 0 || choice > 5) {
    std::cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại (0-5): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return choice;
}

void CustomerView::handleViewBalance() {
  std::cout << "\n=== XEM SỐ DƯ ĐIỂM ===" << std::endl;

  int walletId;
  double balance;

  // Gọi WalletController để lấy thông tin ví của user
  if (controllers::WalletController::getWalletByUserId(userId, walletId,
                                                       balance)) {
    std::cout << "Số dư điểm hiện tại của bạn: " << balance << " điểm"
              << std::endl;
  } else {
    std::cout << "Không tìm thấy ví của bạn hoặc có lỗi xảy ra!" << std::endl;
    std::cout << "Vui lòng liên hệ quản trì viên để được hỗ trợ." << std::endl;
  }

  std::cout << "\nNhấn Enter để tiếp tục...";
  std::cin.ignore();
  std::cin.get();
}

void CustomerView::handleTransfer() {
  std::string username = getInput("Nhập tên đăng nhập người nhận: ");
  std::string amount = getInput("Nhập số điểm muốn chuyển: ");
  // TODO: Gọi WalletController để chuyển điểm
  std::cout << "Chức năng đang được phát triển..." << std::endl;
}

void CustomerView::handleViewTransactionHistory() {
  // TODO: Gọi TransactionController để lấy lịch sử giao dịch
  std::cout << "Chức năng đang được phát triển..." << std::endl;
}

void CustomerView::handleEditProfile() {
  // TODO: Gọi UserController để điều chỉnh thông tin cá nhân
  std::cout << "Chức năng đang được phát triển..." << std::endl;
}

void CustomerView::handleChangePassword() {
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
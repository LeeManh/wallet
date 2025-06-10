#include "views/CustomerView.hpp"

#include <iostream>
#include <limits>

#include "controllers/AuthController.hpp"

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
  // TODO: Gọi WalletController để lấy số dư
  std::cout << "Chức năng đang được phát triển..." << std::endl;
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
  std::string currentPassword = getInput("Nhập mật khẩu hiện tại: ");
  std::string newPassword = getInput("Nhập mật khẩu mới: ");
  std::string confirmPassword = getInput("Nhập lại mật khẩu mới: ");

  // TODO: Gọi AuthController để đổi mật khẩu
  std::cout << "Chức năng đang được phát triển..." << std::endl;
}

}  // namespace views
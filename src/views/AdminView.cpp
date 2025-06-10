#include "views/AdminView.hpp"

#include <iostream>
#include <limits>

#include "controllers/AuthController.hpp"

namespace views {

void AdminView::display() {
  std::cout << "\n=== MENU QUẢN TRỊ VIÊN ===" << std::endl;
  std::cout << "[1] Xem danh sách người dùng" << std::endl;
  std::cout << "[2] Xem danh sách ví" << std::endl;
  std::cout << "[3] Xem lịch sử giao dịch" << std::endl;
  std::cout << "[4] Tạo tài khoản mới cho người dùng" << std::endl;
  std::cout << "[5] Điều chỉnh thông tin người dùng" << std::endl;
  std::cout << "[6] Quản lý ví tổng" << std::endl;
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
  std::string fullName = getInput("Nhập họ và tên: ");

  controllers::AuthController authController;
  std::string generatedPassword;

  if (authController.createUserByAdmin(username, fullName, generatedPassword)) {
    std::cout << "\nTạo tài khoản thành công!" << std::endl;
    std::cout << "Tên đăng nhập: " << username << std::endl;
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
  // TODO: Gọi WalletController để lấy danh sách ví
  std::cout << "Chức năng đang được phát triển..." << std::endl;
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
  // TODO: Gọi WalletController để quản lý ví tổng
  std::cout << "Chức năng đang được phát triển..." << std::endl;
}

void AdminView::handleChangePassword() {
  // TODO: Gọi AuthController để đổi mật khẩu
  std::cout << "Chức năng đang được phát triển..." << std::endl;
}

}  // namespace views
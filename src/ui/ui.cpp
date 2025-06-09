#include "ui/ui.hpp"

using namespace std;

namespace ui {

void UserInterface::displayMainMenu() {
  cout << "\n=== Hệ thống quản lý ví điểm thưởng ===" << endl;
  cout << "1. Đăng nhập" << endl;
  cout << "2. Đăng ký" << endl;
  cout << "3. Thoát" << endl;
  cout << "Nhập lựa chọn (1-3): ";
}

int UserInterface::getMenuChoice() {
  int choice;
  while (!(cin >> choice) || choice < 1 || choice > 3) {
    cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại (1-3): ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  return choice;
}

void UserInterface::handleLogin() {
  cout << "Chức năng đăng nhập đang được phát triển..." << endl;
}

void UserInterface::handleRegistration() {
   cout << "Chức năng đăng ký đang được phát triển..." << endl;
}

}  // namespace ui
#include "views/MainView.hpp"

#include <iostream>
#include <limits>

namespace views {

void MainView::display() {
  std::cout << "\n=== Hệ thống quản lý ví điểm thưởng ===" << std::endl;
  std::cout << "[1] Đăng nhập" << std::endl;
  std::cout << "[2] Đăng ký" << std::endl;
  std::cout << "[0] Thoát" << std::endl;
  std::cout << "Nhập lựa chọn: ";
}

int MainView::getChoice() {
  int choice;
  while (!(std::cin >> choice) || choice < 0 || choice > 2) {
    std::cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại (0-2): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return choice;
}

std::string View::getInput(const std::string& prompt) {
  std::string input;
  std::cout << prompt;
  getline(std::cin, input);
  return input;
}

}  // namespace views
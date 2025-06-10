#include "ui/ui.hpp"

#include <iostream>
#include <limits>
#include <string>

#include "auth/auth.hpp"
#include "utils/input.hpp"
#include "utils/password.hpp"
#include "utils/validation.hpp"

namespace ui {
void UserInterface::displayMainMenu() {
  std::cout << "\n=== Hệ thống quản lý ví điểm thưởng ===" << std::endl;
  std::cout << "[1] Đăng nhập" << std::endl;
  std::cout << "[2] Đăng ký" << std::endl;
  std::cout << "[0] Thoát" << std::endl;
  std::cout << "Nhập lựa chọn: ";
}

int UserInterface::getMenuChoice() {
  int choice;
  while (!(std::cin >> choice) || choice < 0 || choice > 2) {
    std::cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại (0-2): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n');  // Clear the newline
  return choice;
}

std::string UserInterface::getInput(const std::string& prompt) {
  std::string input;
  std::cout << prompt;
  getline(std::cin, input);
  return input;
}

bool UserInterface::handleRegistration() {
  std::cout << "\n=== Đăng ký tài khoản ===" << std::endl;

  // Nhập username
  std::string username = utils::input::getValidatedInput(
      "Nhập tên đăng nhập: ", utils::validation::isValidUsername,
      "- Tên đăng nhập không hợp lệ.\n"
      "- Tên đăng nhập phải có ít nhất 3 ký tự và chỉ chứa chữ cái, số và "
      "dấu "
      "gạch dưới");

  // Nhập password
  std::string password = utils::input::getValidatedInput(
      "Nhập mật khẩu: ", utils::validation::isValidPassword,
      "- Mật khẩu không hợp lệ.\n"
      "- Mật khẩu phải có ít nhất 6 ký tự và không được trống.");

  // Nhập lại password
  std::string confirmPassword;
  do {
    confirmPassword = getInput("Nhập lại mật khẩu: ");
    if (password != confirmPassword) {
      std::cout << "Mật khẩu không khớp. Vui lòng nhập lại." << std::endl;
    }
  } while (password != confirmPassword);

  // Nhập họ tên
  std::string fullName = getInput("Nhập họ và tên: ");

  return auth::registerUser(username, password, fullName);
}

std::pair<bool, bool> UserInterface::handleLogin() {
  std::cout << "\n=== Đăng nhập ===" << std::endl;

  // Nhập username
  std::string username = utils::input::getValidatedInput(
      "Nhập tên đăng nhập: ", utils::validation::isValidUsername,
      "- Tên đăng nhập không hợp lệ.\n"
      "- Tên đăng nhập phải có ít nhất 3 ký tự và chỉ chứa chữ cái, số và "
      "dấu "
      "gạch dưới");

  // Nhập password
  std::string password = utils::input::getValidatedInput(
      "Nhập mật khẩu: ", utils::validation::isValidPassword,
      "- Mật khẩu không hợp lệ.\n"
      "- Mật khẩu phải có ít nhất 6 ký tự và không được trống.");

  return auth::login(username, password);
}

void UserInterface::displayCustomerMenu() {
  std::cout << "\n=== Menu Khách hàng ===" << std::endl;
  std::cout << "[1] Xem thông tin cá nhân" << std::endl;
  std::cout << "[2] Cập nhật thông tin cá nhân" << std::endl;
  std::cout << "[3] Đổi mật khẩu" << std::endl;
  std::cout << "[4] Xem số dư ví" << std::endl;
  std::cout << "[5] Chuyển điểm cho người khác" << std::endl;
  std::cout << "[6] Xem lịch sử giao dịch" << std::endl;
  std::cout << "[0] Đăng xuất" << std::endl;
  std::cout << "Nhập lựa chọn của bạn: ";
}

void UserInterface::displayAdminMenu() {
  std::cout << "\n=== Menu Quản trị viên ===" << std::endl;
  std::cout << "[1] Xem thông tin cá nhân" << std::endl;
  std::cout << "[2] Đổi mật khẩu" << std::endl;
  std::cout << "[3] Xem danh sách người dùng" << std::endl;
  std::cout << "[4] Tạo tài khoản mới cho người dùng" << std::endl;
  std::cout << "[5] Điều chỉnh thông tin tài khoản người dùng" << std::endl;
  std::cout << "[6] Xem số dư ví của người dùng" << std::endl;
  std::cout << "[7] Xem/Tra cứu lịch sử giao dịch" << std::endl;
  std::cout << "[0] Đăng xuất" << std::endl;
  std::cout << "Nhập lựa chọn của bạn: ";
}

int UserInterface::getCustomerMenuChoice() {
  int choice;
  while (!(std::cin >> choice) || choice < 0 || choice > 6) {
    std::cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại (0-6): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return choice;
}

int UserInterface::getAdminMenuChoice() {
  int choice;
  while (!(std::cin >> choice) || choice < 0 || choice > 7) {
    std::cout << "Lựa chọn không hợp lệ. Vui lòng nhập lại (0-7): ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return choice;
}

bool UserInterface::handleAdminCreateAccount() {
  std::cout << "\n=== Tạo tài khoản mới cho người dùng ===" << std::endl;

  // Nhập username
  std::string username = utils::input::getValidatedInput(
      "Nhập tên đăng nhập: ", utils::validation::isValidUsername,
      "- Tên đăng nhập không hợp lệ.\n"
      "- Tên đăng nhập phải có ít nhất 3 ký tự và chỉ chứa chữ cái, số và "
      "dấu gạch dưới");

  // Nhập họ tên
  std::string fullName = getInput("Nhập họ và tên: ");

  // Tạo mật khẩu ngẫu nhiên
  std::string password = utils::password::generateRandomPassword(8);

  // Đăng ký tài khoản
  bool success = auth::registerUser(username, password, fullName);

  if (success) {
    std::cout << "\nTạo tài khoản thành công!" << std::endl;
    std::cout << "Thông tin đăng nhập:" << std::endl;
    std::cout << "Tên đăng nhập: " << username << std::endl;
    std::cout << "Mật khẩu: " << password << std::endl;
    std::cout << "\nVui lòng lưu lại thông tin đăng nhập này và chuyển cho "
                 "người dùng."
              << std::endl;
  }

  return success;
}

}  // namespace ui
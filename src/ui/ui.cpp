#include "ui/ui.hpp"

#include <iostream>
#include <limits>
#include <string>

#include "auth/auth.hpp"
#include "utils/validation.hpp"

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
  cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the newline
  return choice;
}

string UserInterface::getInput(const string& prompt) {
  string input;
  cout << prompt;
  getline(cin, input);
  return input;
}

bool UserInterface::handleRegistration() {
  cout << "\n=== Đăng ký tài khoản ===" << endl;

  // Nhập username
  string username;
  do {
    username = getInput("Nhập tên đăng nhập: ");
    if (!utils::validation::isValidUsername(username)) {
      cout << "- Tên đăng nhập không hợp lệ." << endl;
      cout << "- Tên đăng nhập phải có ít nhất 3 ký "
              "tự và chỉ chứa chữ cái, số và dấu gạch dưới"
           << endl;
    }
  } while (!utils::validation::isValidUsername(username));

  // Nhập password
  string password;
  do {
    password = getInput("Nhập mật khẩu: ");
    if (!utils::validation::isValidPassword(password)) {
      cout << "- Mật khẩu không hợp lệ." << endl;
      cout << "- Mật khẩu phải có ít nhất 6 ký tự và "
              "không được trống."
           << endl;
    }
  } while (!utils::validation::isValidPassword(password));

  // Nhập lại password
  string confirmPassword;
  do {
    confirmPassword = getInput("Nhập lại mật khẩu: ");
    if (password != confirmPassword) {
      cout << "Mật khẩu không khớp. Vui lòng nhập lại." << endl;
    }
  } while (password != confirmPassword);

  // Nhập họ tên
  string fullName = getInput("Nhập họ và tên: ");

  return auth::registerUser(username, password, fullName);
}

bool UserInterface::handleLogin() {
  cout << "\n=== Đăng nhập ===" << endl;

  // Nhập username
  string username;
  do {
    username = getInput("Nhập tên đăng nhập: ");
    if (!utils::validation::isValidUsername(username)) {
      cout << "- Tên đăng nhập không hợp lệ." << endl;
      cout << "- Tên đăng nhập phải có ít nhất 3 ký "
              "tự và chỉ chứa chữ cái, số và dấu gạch dưới"
           << endl;
    }
  } while (!utils::validation::isValidUsername(username));

  // Nhập password
  string password;
  do {
    password = getInput("Nhập mật khẩu: ");
    if (!utils::validation::isValidPassword(password)) {
      cout << "- Mật khẩu không hợp lệ." << endl;
      cout << "- Mật khẩu phải có ít nhất 6 ký tự và "
              "không được trống."
           << endl;
    }
  } while (!utils::validation::isValidPassword(password));

  return auth::login(username, password);
}

}  // namespace ui
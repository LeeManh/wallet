#include "ui/ui.hpp"

#include <termios.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <regex>

using namespace std;
using json = nlohmann::json;

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

bool UserInterface::isValidUsername(const string& username) {
  // Username phải có ít nhất 3 ký tự, chỉ chứa chữ cái, số và dấu gạch dưới
  regex pattern("^[a-zA-Z0-9_]{3,}$");
  return regex_match(username, pattern);
}

bool UserInterface::isValidPassword(const string& password) {
  // Password phải có ít nhất 6 ký tự và không được trống
  return password.length() >= 6 && !password.empty();
}

bool UserInterface::handleRegistration() {
  cout << "\n=== Đăng ký tài khoản ===" << endl;

  // Nhập username
  string username;
  do {
    username = getInput("Nhập tên đăng nhập: ");
    if (!isValidUsername(username)) {
      cout << "- Tên đăng nhập không hợp lệ." << endl;
      cout << "- Tên đăng nhập phải có ít nhất 3 ký "
              "tự và chỉ chứa chữ cái, số và dấu gạch dưới"
           << endl;
    }
  } while (!isValidUsername(username));

  // Nhập password
  string password;
  do {
    password = getInput("Nhập mật khẩu: ");
    if (!isValidPassword(password)) {
      cout << "- Mật khẩu không hợp lệ." << endl;
      cout << "- Mật khẩu phải có ít nhất 6 ký tự và "
              "không được trống."
           << endl;
    }
  } while (!isValidPassword(password));

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

  try {
    // Tạo đối tượng User
    user::User newUser(username, password, fullName);

    // Đọc file users.json hiện tại
    json users = json::array();
    ifstream file("data/users.json");
    if (file.is_open()) {
      file >> users;
      file.close();
    } else {
      cout << "Không thể mở file users.json" << endl;
    }

    // Thêm thông tin người dùng mới
    json userData;
    userData["username"] = newUser.getUsername();
    userData["passwordHash"] = newUser.getPasswordHash();
    userData["fullName"] = newUser.getFullName();
    userData["isAdmin"] = newUser.isAdminUser();

    users.push_back(userData);

    // Lưu user vào file
    ofstream outFile("data/users.json");
    outFile << setw(4) << users << endl;
    outFile.close();

    cout << "Đăng ký thành công!" << endl;
    return true;
  } catch (const exception& e) {
    cout << "Lỗi: " << e.what() << endl;
    return false;
  }
}

bool UserInterface::handleLogin() {
  cout << "\n=== Đăng nhập ===" << endl;

  // Nhập username
  string username;
  do {
    username = getInput("Nhập tên đăng nhập: ");
    if (!isValidUsername(username)) {
      cout << "- Tên đăng nhập không hợp lệ." << endl;
      cout << "- Tên đăng nhập phải có ít nhất 3 ký "
              "tự và chỉ chứa chữ cái, số và dấu gạch dưới"
           << endl;
    }
  } while (!isValidUsername(username));

  // Nhập password
  string password;
  do {
    password = getInput("Nhập mật khẩu: ");
    if (!isValidPassword(password)) {
      cout << "- Mật khẩu không hợp lệ." << endl;
      cout << "- Mật khẩu phải có ít nhất 6 ký tự và "
              "không được trống."
           << endl;
    }
  } while (!isValidPassword(password));

  try {
    // Đọc file users.json
    json users;
    ifstream file("data/users.json");
    if (!file.is_open()) {
      cout << "Không thể mở file users.json" << endl;
      return false;
    }
    file >> users;
    file.close();

    for (const auto& user : users) {
      if (user["username"] == username) {
        user::User tempUser(user["username"], user["passwordHash"],
                            user["fullName"]);

        bool isMathPassword = tempUser.verifyPassword(password);
        if (!isMathPassword) break;

        cout << "Đăng nhập thành công!" << endl;
        cout << "Xin chào " << user["fullName"] << endl;
        return true;
      }
    }

    cout << "Tên đăng nhập hoặc mật khẩu không đúng!" << endl;
    return false;

  } catch (const exception& e) {
    cout << "Lỗi: " << e.what() << endl;
    return false;
  }
}

}  // namespace ui
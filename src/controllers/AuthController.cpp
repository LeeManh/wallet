#include "controllers/AuthController.hpp"

#include <iostream>

#include "utils/hash.hpp"
#include "utils/password.hpp"
#include "utils/storage.hpp"

namespace controllers {

std::pair<bool, bool> AuthController::login(const std::string& username,
                                            const std::string& password) {
  try {
    // Đọc file users.json
    json users = utils::storage::readJsonFile("data/users.json");

    for (const auto& user : users) {
      if (user["username"] == username) {
        bool isMathPassword =
            utils::hash::validatePassword(password, user["passwordHash"]);

        if (!isMathPassword) break;

        std::cout << "Đăng nhập thành công!" << std::endl;
        return {true, user["isAdmin"]};
      }
    }

    std::cout << "Tên đăng nhập hoặc mật khẩu không đúng!" << std::endl;
    return {false, false};

  } catch (const std::exception& e) {
    std::cout << "Lỗi: " << e.what() << std::endl;
    return {false, false};
  }
}

bool AuthController::registerUser(const std::string& username,
                                  const std::string& password,
                                  const std::string& fullName) {
  try {
    // Đọc file users.json hiện tại
    json users = utils::storage::readJsonFile("data/users.json");

    // Kiểm tra username đã tồn tại chưa
    for (const auto& user : users) {
      if (user["username"] == username) {
        std::cout << "Tên đăng nhập đã tồn tại!" << std::endl;
        return false;
      }
    }

    // Tạo đối tượng User
    std::string passwordHash = utils::hash::generatePasswordHash(password);
    models::User newUser(username, passwordHash, fullName);

    // Thêm thông tin người dùng mới
    json userData;
    userData["username"] = newUser.getUsername();
    userData["passwordHash"] = newUser.getPasswordHash();
    userData["fullName"] = newUser.getFullName();
    userData["isAdmin"] = newUser.isAdminUser();

    users.push_back(userData);

    // Đảm bảo thư mục data tồn tại
    if (!utils::storage::ensureDirectoryExists("data")) {
      std::cout << "Không thể tạo thư mục data!" << std::endl;
      return false;
    }

    // Lưu user vào file
    if (!utils::storage::writeJsonFile("data/users.json", users)) {
      std::cout << "Không thể lưu thông tin người dùng!" << std::endl;
      return false;
    }

    std::cout << "Đăng ký thành công!" << std::endl;
    return true;
  } catch (const std::exception& e) {
    std::cout << "Lỗi: " << e.what() << std::endl;
    return false;
  }
}

bool AuthController::createUserByAdmin(const std::string& username,
                                       const std::string& fullName,
                                       std::string& generatedPassword) {
  // Tạo mật khẩu ngẫu nhiên
  generatedPassword = utils::password::generateRandomPassword(8);

  // Đăng ký user với mật khẩu đã tạo
  return registerUser(username, generatedPassword, fullName);
}

}  // namespace controllers
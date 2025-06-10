#include "auth/auth.hpp"

#include "utils/hash.hpp"
#include "utils/storage.hpp"

namespace auth {

bool isUserExists(const json& users, const std::string& username) {
  for (const auto& user : users) {
    if (user["username"] == username) {
      return true;
    }
  }
  return false;
}

std::pair<bool, bool> login(const std::string& username,
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

bool registerUser(const std::string& username, const std::string& password,
                  const std::string& fullName) {
  try {
    // Đọc file users.json hiện tại
    json users = utils::storage::readJsonFile("data/users.json");

    // Kiểm tra username đã tồn tại chưa
    if (isUserExists(users, username)) {
      std::cout << "Tài khoản đã tồn tại!" << std::endl;
      return false;
    }

    // Tạo đối tượng User
    std::string passwordHash = utils::hash::generatePasswordHash(password);
    user::User newUser(username, passwordHash, fullName);

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

}  // namespace auth
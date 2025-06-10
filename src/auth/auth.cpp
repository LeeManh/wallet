#include "auth/auth.hpp"

#include "utils/hash.hpp"
#include "utils/storage.hpp"

namespace auth {

bool login(const std::string& username, const std::string& password) {
  try {
    // Đọc file users.json
    json users = utils::storage::readJsonFile("data/users.json");

    for (const auto& user : users) {
      if (user["username"] == username) {
        bool isMathPassword =
            utils::hash::validatePassword(password, user["passwordHash"]);

        if (!isMathPassword) break;

        std::cout << "Đăng nhập thành công!" << std::endl;
        std::cout << "Xin chào " << user["fullName"] << std::endl;
        return true;
      }
    }

    std::cout << "Tên đăng nhập hoặc mật khẩu không đúng!" << std::endl;
    return false;

  } catch (const std::exception& e) {
    std::cout << "Lỗi: " << e.what() << std::endl;
    return false;
  }
}
bool registerUser(const std::string& username, const std::string& password,
                  const std::string& fullName) {
  try {
    // Tạo đối tượng User
    std::string passwordHash = utils::hash::generatePasswordHash(password);
    user::User newUser(username, passwordHash, fullName);

    // Đọc file users.json hiện tại
    json users = utils::storage::readJsonFile("data/users.json");

    // Thêm thông tin người dùng mới
    json userData;
    userData["username"] = newUser.getUsername();
    userData["passwordHash"] = newUser.getPasswordHash();
    userData["fullName"] = newUser.getFullName();
    userData["isAdmin"] = newUser.isAdminUser();

    users.push_back(userData);

    // Lưu user vào file
    if (!utils::storage::writeJsonFile("data/users.json", users)) {
      std::cout << "Không thể lưu thông tin người dùng" << std::endl;
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
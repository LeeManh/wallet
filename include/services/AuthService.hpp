#pragma once

#include <string>
#include <tuple>

#include "services/UserService.hpp"

namespace services {

class AuthService {
 public:
  // Đăng nhập
  static std::tuple<bool, int, bool> login(const std::string& username,
                                           const std::string& password);

  // Người dùng đăng kí
  static bool registerUser(const std::string& username,
                           const std::string& password,
                           const std::string& email,
                           const std::string& fullName);

  // Admin tạo tài khoản
  static bool registerUserByAdmin(const std::string& username,
                                  const std::string& email,
                                  const std::string& fullName,
                                  std::string& generatedPassword);

  // Người dùng tự đổi mật khẩu
  static bool changePassword(int userId, const std::string& currentPassword,
                             const std::string& newPassword);

  // Admin cập nhập mật khẩu cho người dùng
  static bool updateUserPassword(int userId, const std::string& newPassword);
};

}  // namespace services
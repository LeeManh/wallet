#ifndef AUTH_CONTROLLER_HPP
#define AUTH_CONTROLLER_HPP

#include <string>
#include <utility>

#include "models/User.hpp"

namespace controllers {

class AuthController {
 public:
  // Đăng nhập
  std::tuple<bool, int, bool> login(const std::string& username,
                                    const std::string& password);

  // Đăng ký
  bool registerUser(const std::string& username, const std::string& password,
                    const std::string& email, const std::string& fullName);

  // Tạo tài khoản bởi admin
  bool createUserByAdmin(const std::string& username, const std::string& email,
                         const std::string& fullName,
                         std::string& generatedPassword);
  // Đổi mật khẩu
  bool changePassword(const int userId, const std::string& currentPassword,
                      const std::string& newPassword);
};

}  // namespace controllers

#endif
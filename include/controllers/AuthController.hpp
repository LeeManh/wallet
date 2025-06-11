#ifndef AUTH_CONTROLLER_HPP
#define AUTH_CONTROLLER_HPP

#include <string>
#include <utility>

#include "models/User.hpp"

namespace controllers {

class AuthController {
 public:
  // Đăng nhập
  std::pair<bool, bool> login(const std::string& username,
                              const std::string& password);

  // Đăng ký
  bool registerUser(const std::string& username, const std::string& password,
                    const std::string& email, const std::string& fullName);

  // Tạo tài khoản bởi admin
  bool createUserByAdmin(const std::string& username, const std::string& email,
                         const std::string& fullName,
                         std::string& generatedPassword);

  // Gửi mã OTP
  bool sendOTP(const std::string& email);

  // Xác thực mã OTP
  bool verifyOTP(const std::string& email, const std::string& otp);

 private:
  // Lưu trữ OTP tạm thời
  std::string currentOTP;
  time_t otpTime;
};

}  // namespace controllers

#endif
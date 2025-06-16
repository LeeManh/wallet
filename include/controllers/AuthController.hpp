#pragma once

#include <string>
#include <tuple>

#include "services/AuthService.hpp"

namespace controllers {

class AuthController {
 public:
  static std::tuple<bool, int, bool> login(const std::string& username,
                                           const std::string& password);

  static bool registerUser(const std::string& username,
                           const std::string& password,
                           const std::string& email,
                           const std::string& fullName);

  static bool registerUserByAdmin(const std::string& username,
                                  const std::string& email,
                                  const std::string& fullName,
                                  std::string& generatedPassword);

  static bool changePassword(const int userId,
                             const std::string& currentPassword,
                             const std::string& newPassword);

  static bool sendOTPInfoChange(const int userId);

  static bool verifyOTPAndChangePassword(const int userId,
                                         const std::string& otpCode,
                                         const std::string& currentPassword,
                                         const std::string& newPassword);
};

}  // namespace controllers
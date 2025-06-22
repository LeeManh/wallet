#pragma once

#include <string>
#include <tuple>

#include "services/AuthService.hpp"

namespace controllers {

class AuthController {
 public:
  static std::tuple<bool, int, bool> login(const std::string& username,
                                           const std::string& password);

  static void registerUser(const std::string& username,
                           const std::string& password,
                           const std::string& email,
                           const std::string& fullName);

  static void registerUserByAdmin(const std::string& username,
                                  const std::string& email,
                                  const std::string& fullName,
                                  std::string& generatedPassword);

  static void changePasswordWithOTP(const int userId,
                                    const std::string& currentPassword,
                                    const std::string& newPassword);
};

}  // namespace controllers
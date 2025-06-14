#pragma once

#include <string>
#include <tuple>

#include "services/UserService.hpp"

namespace services {

class AuthService {
 public:
  // Authentication methods
  std::tuple<bool, int, bool> login(const std::string& username,
                                    const std::string& password);
  bool registerUser(const std::string& username, const std::string& password,
                    const std::string& email, const std::string& fullName);
  bool registerUserByAdmin(const std::string& username,
                           const std::string& email,
                           const std::string& fullName,
                           std::string& generatedPassword);

  // Password management
  bool changePassword(int userId, const std::string& currentPassword,
                      const std::string& newPassword);
  bool updateUserPassword(int userId, const std::string& newPassword);

 private:
  UserService userService;
};

}  // namespace services
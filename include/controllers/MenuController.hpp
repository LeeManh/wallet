#pragma once

#include "controllers/AuthController.hpp"

namespace controllers {

class MenuController {
 public:
  static void handleLogin(const std::string& username,
                          const std::string& password);

  static void handleRegistration();
};

}  // namespace controllers

#ifndef MENU_CONTROLLER_HPP
#define MENU_CONTROLLER_HPP

#include "controllers/AuthController.hpp"

namespace controllers {

class MenuController {
 private:
  AuthController authController;

 public:
  void handleLogin(const std::string& username, const std::string& password);
  void handleRegistration();
};

}  // namespace controllers

#endif
#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <limits>
#include <string>

#include "user/user.hpp"

namespace ui {

class UserInterface {
 private:
  static std::string getInput(const std::string& prompt);
  static bool isValidUsername(const std::string& username);
  static bool isValidPassword(const std::string& password);

 public:
  static void displayMainMenu();
  static int getMenuChoice();
  static bool handleLogin();
  static bool handleRegistration();
};

}  // namespace ui

#endif
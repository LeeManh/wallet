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

 public:
  static void displayMainMenu();
  static int getMenuChoice();
  static std::pair<bool, bool> handleLogin();
  static bool handleRegistration();
  static void displayCustomerMenu();
  static void displayAdminMenu();
  static int getCustomerMenuChoice();
  static int getAdminMenuChoice();
  static bool handleAdminCreateAccount();
};

}  // namespace ui

#endif
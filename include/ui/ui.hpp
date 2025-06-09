#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <limits>

namespace ui {

class UserInterface {
 public:
  static void displayMainMenu();
  static int getMenuChoice();
  static void handleLogin();
  static void handleRegistration();
};

}  // namespace ui

#endif
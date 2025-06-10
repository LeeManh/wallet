#include <iostream>

#include "ui/ui.hpp"

using namespace std;

int main() {
  while (true) {
    ui::UserInterface::displayMainMenu();
    int choice = ui::UserInterface::getMenuChoice();

    switch (choice) {
      case 1: {
        auto [success, isAdmin] = ui::UserInterface::handleLogin();

        if (success) {
          while (true) {
            if (isAdmin) {
              ui::UserInterface::displayAdminMenu();
              int adminChoice = ui::UserInterface::getAdminMenuChoice();
              if (adminChoice == 0) break;
              // Handle admin menu choices
            } else {
              ui::UserInterface::displayCustomerMenu();
              int customerChoice = ui::UserInterface::getCustomerMenuChoice();
              if (customerChoice == 0) break;
              // Handle customer menu choices
            }
          }
        }
        break;
      }
      case 2:
        ui::UserInterface::handleRegistration();
        break;
      case 0:
        cout << "Cảm ơn bạn đã sử dụng chương trình!" << endl;
        return 0;
    }
  }

  return 0;
}
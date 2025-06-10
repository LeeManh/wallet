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
              switch (adminChoice) {
                case 4:  // Tạo tài khoản mới cho người dùng
                  ui::UserInterface::handleAdminCreateAccount();
                  break;
                // Handle other admin menu choices
                default:
                  cout << "Chức năng đang được phát triển..." << endl;
                  break;
              }
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
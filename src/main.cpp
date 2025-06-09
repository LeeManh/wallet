#include <iostream>

#include "ui/ui.hpp"

using namespace std;

int main() {
  while (true) {
    ui::UserInterface::displayMainMenu();
    int choice = ui::UserInterface::getMenuChoice();

    switch (choice) {
      case 1:
        ui::UserInterface::handleLogin();
        break;
      case 2:
        ui::UserInterface::handleRegistration();
        break;
      case 3:
        cout << "Cảm ơn bạn đã sử dụng chương trình!" << endl;
        return 0;
    }
  }

  return 0;
}
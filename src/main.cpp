#include <iostream>

#include "controllers/AuthController.hpp"
#include "views/AdminView.hpp"
#include "views/CustomerView.hpp"
#include "views/MainView.hpp"
#include "views/RegistrationView.hpp"

using namespace std;

int main() {
  views::MainView mainView;
  views::AdminView adminView;
  views::CustomerView customerView;
  views::RegistrationView registrationView;
  controllers::AuthController authController;

  while (true) {
    mainView.display();
    int choice = mainView.getChoice();

    switch (choice) {
      case 1: {
        cout << "\n=== Đăng nhập ===" << endl;
        string username = mainView.getInput("Nhập tên đăng nhập: ");
        string password = mainView.getInput("Nhập mật khẩu: ");
        auto [success, isAdmin] = authController.login(username, password);

        if (success) {
          while (true) {
            if (isAdmin) {
              adminView.display();
              int adminChoice = adminView.getChoice();
              if (adminChoice == 0) break;

              switch (adminChoice) {
                case 1:
                  adminView.handleViewAllUsers();
                  break;
                case 2:
                  adminView.handleViewAllWallets();
                  break;
                case 3:
                  adminView.handleViewTransactionHistory();
                  break;
                case 4:
                  adminView.handleCreateAccount();
                  break;
                case 5:
                  adminView.handleEditUserInfo();
                  break;
                case 6:
                  adminView.handleManageTotalWallet();
                  break;
                case 7:
                  adminView.handleChangePassword();
                  break;
              }
            } else {
              customerView.display();
              int customerChoice = customerView.getChoice();
              if (customerChoice == 0) break;

              switch (customerChoice) {
                case 1:
                  customerView.handleViewBalance();
                  break;
                case 2:
                  customerView.handleDeposit();
                  break;
                case 3:
                  customerView.handleWithdraw();
                  break;
                case 4:
                  customerView.handleTransfer();
                  break;
                case 5:
                  customerView.handleViewTransactionHistory();
                  break;
                case 6:
                  customerView.handleEditProfile();
                  break;
                case 7:
                  customerView.handleChangePassword();
                  break;
              }
            }
          }
        }
        break;
      }
      case 2:
        registrationView.display();
        registrationView.handleRegistration();
        break;
      case 0:
        cout << "Cảm ơn bạn đã sử dụng chương trình!" << endl;
        return 0;
    }
  }

  return 0;
}
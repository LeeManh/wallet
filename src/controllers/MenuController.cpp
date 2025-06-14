#include "controllers/MenuController.hpp"

#include "views/AdminView.hpp"
#include "views/CustomerView.hpp"
#include "views/RegistrationView.hpp"

namespace controllers {

void MenuController::handleLogin(const std::string& username,
                                 const std::string& password) {
  auto [success, userId, isAdmin] = authController.login(username, password);

  if (success) {
    if (isAdmin) {
      views::AdminView adminView;
      adminView.userId = userId;
      adminView.display();
    } else {
      views::CustomerView customerView;
      customerView.userId = userId;
      customerView.display();
    }
  }
}

void MenuController::handleRegistration() {
  views::RegistrationView registrationView;
  registrationView.display();
}

}  // namespace controllers
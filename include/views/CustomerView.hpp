#pragma once

#include "models/User.hpp"

namespace views {

class CustomerView {
 public:
  int userId;

  void display();

  // Các phương thức xử lý menu customer
  void handleViewBalance();
  void handleTransfer();
  void handleViewTransactionHistory();
  void handleEditProfile();
  void handleChangePassword();
};

}  // namespace views

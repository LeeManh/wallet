#pragma once

#include "models/User.hpp"

namespace views {

class CustomerView {
 public:
  int userId;

  void display();

  // Các phương thức xử lý menu customer
  void handleViewBalance();
  void handleTransferPoints();
  void handleViewTransactionHistory();
  void handleEditProfile();
  void handleChangePassword();
  void handleViewProfile();
};

}  // namespace views

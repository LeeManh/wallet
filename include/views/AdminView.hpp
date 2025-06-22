#pragma once

#include "utils/Format.hpp"

namespace views {

class AdminView {
 public:
  int userId;

  void display();

  // Các phương thức xử lý menu admin
  void handleCreateAccount();
  void handleViewAllUsers();
  void handleViewAllWallets();
  void handleViewTransactionHistory();
  void handleEditUserInfo();
  void handleManageTotalWallet();
  void handleChangePassword();
};

}  // namespace views

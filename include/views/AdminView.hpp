#pragma once

#include "utils/Format.hpp"
#include "views/View.hpp"

namespace views {

class AdminView : public View {
 public:
  int userId;
  void display() override;

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

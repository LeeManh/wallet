#ifndef ADMIN_VIEW_HPP
#define ADMIN_VIEW_HPP

#include "views/View.hpp"

namespace views {

class AdminView : public View {
 public:
  void display() override;
  int getChoice() override;

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

#endif
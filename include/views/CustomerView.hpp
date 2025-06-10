#ifndef CUSTOMER_VIEW_HPP
#define CUSTOMER_VIEW_HPP

#include "views/View.hpp"

namespace views {

class CustomerView : public View {
 public:
  void display() override;
  int getChoice() override;

  // Các phương thức xử lý menu customer
  void handleViewBalance();
  void handleTransfer();
  void handleViewTransactionHistory();
  void handleEditProfile();
  void handleChangePassword();
};

}  // namespace views

#endif
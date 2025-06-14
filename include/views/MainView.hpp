#pragma once

#include "views/View.hpp"

namespace views {

class MainView : public View {
 public:
  void display() override;

  // Các phương thức xử lý menu
  void handleLogin();
  void handleRegistration();
};

}  // namespace views

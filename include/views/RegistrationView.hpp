#ifndef REGISTRATION_VIEW_HPP
#define REGISTRATION_VIEW_HPP

#include "views/View.hpp"

namespace views {

class RegistrationView : public View {
 public:
  void display() override;
  int getChoice() override;
  void handleRegistration();
};

}  // namespace views

#endif
#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include "views/View.hpp"

namespace views {

class MainView : public View {
 public:
  void display() override;
  int getChoice() override;
};

}  // namespace views

#endif
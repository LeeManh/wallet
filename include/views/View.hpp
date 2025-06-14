#pragma once

#include <iostream>
#include <string>

namespace views {

class View {
 public:
  static std::string getInput(const std::string& prompt);
  virtual void display() = 0;
  virtual int getChoice(int min, int max);
};

}  // namespace views

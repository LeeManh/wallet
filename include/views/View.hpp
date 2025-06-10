#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>
#include <string>

namespace views {

class View {
 public:
  static std::string getInput(const std::string& prompt);
  virtual void display() = 0;
  virtual int getChoice() = 0;
};

}  // namespace views

#endif
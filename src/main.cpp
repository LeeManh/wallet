#include <iostream>

using namespace std;

#include "models/User.hpp"
#include "seeds/MySeed.hpp"
#include "views/MainView.hpp"

int main() {
  seeds::Seed::initialize();

  views::MainView mainView;
  mainView.display();

  return 0;
}

#include <iostream>
#include "utils/Utf8Console.hpp"
#include "models/User.hpp"
#include "seeds/MySeed.hpp"
#include "views/MainView.hpp"
using namespace std;
int main() {
  seeds::Seed::initialize();

  views::MainView mainView;
  mainView.display();

 // Bật UTF-8 cho console (Windows)
  vnconsole::initVietnameseConsole();
  
  return 0;
}

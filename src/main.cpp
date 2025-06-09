#include <iostream>

#include "utils/calculator.hpp"

using namespace std;
using namespace utils;

int main() {
  int x = 5, y = 7;
  cout << "Tong cua " << x << " + " << y << " = " << tinhTong(x, y) << endl;
  return 0;
}
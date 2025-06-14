#include "utils/Format.hpp"

#include <iomanip>
#include <sstream>

namespace utils::format {

std::string formatPoint(double amount, int decimalPlaces) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(decimalPlaces);
  ss << amount;
  return ss.str();
}

}  // namespace utils::format
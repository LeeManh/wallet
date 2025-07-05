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
  // Count the number of UTF-8 code points in a string
int utf8_codepoint_count(const std::string& s) {
    int count = 0;
    for (size_t i = 0; i < s.size(); ) {
        unsigned char c = s[i];
        if      (c < 0x80) i += 1; // ASCII
        else if (c < 0xE0) i += 2; // 2-byte sequence
        else if (c < 0xF0) i += 3; // 3-byte sequence
        else if (c < 0xF8) i += 4; // 4-byte sequence
        else i += 1; // Invalid UTF-8, skip
        ++count;
    }
    return count;
}

std::string formatCell(const std::string& value, int space) {
    int visibleLen = utf8_codepoint_count(value);
    std::string result = value;
    // Pad with spaces until visibleLen == space
    while (visibleLen < space) {
        result += ' ';
        ++visibleLen;
    }
    return result;
}
std::string formatBorder(int width) {
    return std::string(width, '-');
}
}  // namespace utils::format
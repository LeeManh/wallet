#pragma once
#include <string>

namespace utils {
namespace format {

    std::string formatPoint(double value, int precision = 2);
    std::string formatCell(const std::string& value, int space);
    std::string formatBorder(int width);
    int utf8_codepoint_count(const std::string& str);

    }
}  // namespace utils
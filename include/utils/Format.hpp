#pragma once
#include <string>
#include <vector>

namespace utils {
namespace format {

std::string formatPoint(double value, int precision = 2);
std::string formatCell(const std::string& value, int space);
std::string formatBorder(int width);
int utf8_codepoint_count(const std::string& str);
std::vector<std::string> wrapText(const std::string& text, size_t width);
std::string padRight(const std::string& str, int width);

}  // namespace format
}  // namespace utils
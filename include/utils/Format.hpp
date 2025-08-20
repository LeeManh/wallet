#pragma once
#include <string>
#include <enums/Enums.hpp>
namespace utils {
    namespace format {

        std::string formatPoint(double value, int precision = 2);
        std::string formatCell(const std::string& value, int space);
        std::string formatBorder(int width);
        int utf8_codepoint_count(const std::string& str);
        std::string to_string(enums::UserInfo info);
        int getCellSize(enums::UserInfo info);
        std::string to_string(enums::WalletInfo info);
        int getCellSize(enums::WalletInfo info);
    }
}  // namespace utils
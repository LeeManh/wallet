#include "utils/Format.hpp"

#include <iomanip>
#include <sstream>
#include <enums/Enums.hpp>
namespace utils::format {
/**
 * @brief Định dạng số thực thành chuỗi với số chữ số thập phân cố định.
 *
 * Input:
 *   - amount: Giá trị số thực.
 *   - decimalPlaces: Số chữ số thập phân cần hiển thị.
 *
 * Output:
 *   - Chuỗi số đã định dạng (ví dụ: 123.45).
 *
 * Thủ tục xử lý:
 *   1. Tạo stringstream và cấu hình hiển thị số thực với std::fixed.
 *   2. Đặt số chữ số thập phân bằng std::setprecision.
 *   3. Ghi giá trị amount vào stream và trả về chuỗi kết quả.
 */
  std::string formatPoint(double amount, int decimalPlaces) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(decimalPlaces);
    ss << amount;
    return ss.str();
  }

/**
 * @brief Đếm số ký tự (code point) trong chuỗi UTF-8.
 *
 * Input:
 *   - s: Chuỗi UTF-8.
 *
 * Output:
 *   - Số lượng code point (ký tự hiển thị).
 *
 * Thủ tục xử lý:
 *   1. Duyệt từng byte của chuỗi.
 *   2. Xác định số byte của mỗi ký tự UTF-8 dựa vào giá trị byte đầu.
 *   3. Tăng biến đếm cho mỗi ký tự.
 */
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

/**
 * @brief Định dạng một ô dữ liệu để canh lề và đảm bảo chiều rộng cố định.
 *
 * Input:
 *   - value: Nội dung ô.
 *   - space: Chiều rộng mong muốn.
 *
 * Output:
 *   - Chuỗi đã bổ sung khoảng trắng để đủ độ rộng.
 *
 * Thủ tục xử lý:
 *   1. Tính độ dài hiển thị thực tế của value (kể cả UTF-8).
 *   2. Thêm khoảng trắng vào cuối cho đến khi đạt độ rộng space.
 *   3. Trả về chuỗi kết quả.
 */
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

/**
 * @brief Tạo chuỗi viền bảng bằng ký tự '-'.
 *
 * Input:
 *   - width: Số lượng ký tự '-'.
 *
 * Output:
 *   - Chuỗi gồm width ký tự '-'.
 */
std::string formatBorder(int width) {
    return std::string(width, '-');
}

std::string to_string(enums::UserInfo info) {
  switch (info) {
    case enums::UserInfo::USERNAME: return "Tên đăng nhập";
    case enums::UserInfo::EMAIL: return "Email";
    case enums::UserInfo::FULL_NAME: return "Họ và tên";
    case enums::UserInfo::ID: return "ID";
    default: return "UNKNOWN";
  }
}

int getCellSize(enums::UserInfo info) {
    switch (info) {
        case enums::UserInfo::ID: return static_cast<int>(enums::CellSize::ID);
        case enums::UserInfo::USERNAME: return static_cast<int>(enums::CellSize::USERNAME);
        case enums::UserInfo::EMAIL: return static_cast<int>(enums::CellSize::EMAIL);
        case enums::UserInfo::FULL_NAME: return static_cast<int>(enums::CellSize::FULL_NAME);
        default: return 0;
    }
}
std::string to_string(enums::WalletInfo info) {
  switch (info) {
    case enums::WalletInfo::WALLET_ID: return "Ví ID";
    case enums::WalletInfo::USER_ID: return "User ID";
    case enums::WalletInfo::WALLET_TYPE: return "Loại ví";
    case enums::WalletInfo::POINT: return "Số điểm";
    default: return "UNKNOWN";
  }
}

int getCellSize(enums::WalletInfo info) {
    switch (info) {
        case enums::WalletInfo::WALLET_ID: return static_cast<int>(enums::CellSize::WALLET_ID);
        case enums::WalletInfo::USER_ID: return static_cast<int>(enums::CellSize::USER_ID);
        case enums::WalletInfo::WALLET_TYPE: return static_cast<int>(enums::CellSize::WALLET_TYPE);
        case enums::WalletInfo::POINT: return static_cast<int>(enums::CellSize::POINT);
        default: return 0;
    }
}
}  // namespace utils::format
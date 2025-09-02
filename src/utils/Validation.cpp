#include "utils/Validation.hpp"

#include <regex>
#include <string>

namespace utils {
namespace validation {

/**
 * @brief Kiểm tra tên người dùng (username).
 *
 * Quy tắc:
 *  - Chỉ cho phép ký tự chữ (a–z, A–Z), số (0–9), gạch dưới (_).
 *  - Độ dài tối thiểu: 3 ký tự.
 *
 * @param username Chuỗi tên người dùng cần kiểm tra.
 * @return true nếu hợp lệ, false nếu không.
 */
bool isValidUsername(const std::string& username) {
  std::regex pattern("^[a-zA-Z0-9_]{3,}$");
  return std::regex_match(username, pattern);
}

/**
 * @brief Kiểm tra mật khẩu.
 *
 * Quy tắc:
 *  - Độ dài tối thiểu: 6 ký tự.
 *  - Không được để trống.
 *
 * @param password Chuỗi mật khẩu cần kiểm tra.
 * @return true nếu hợp lệ, false nếu không.
 */
bool isValidPassword(const std::string& password) {
  return password.length() >= 6 && !password.empty();
}

/**
 * @brief Kiểm tra số nguyên dương từ chuỗi.
 *
 * Quy tắc:
 *  - Chỉ bao gồm ký tự số (0–9).
 *  - Không chứa ký tự khác.
 *
 * @param number Chuỗi cần kiểm tra.
 * @return true nếu hợp lệ, false nếu không.
 */
bool isPositiveNumber(const std::string& number) {
  return std::regex_match(number, std::regex("^[0-9]+$"));
}

/**
 * @brief Kiểm tra số nguyên dương từ kiểu int.
 *
 * @param number Số nguyên cần kiểm tra.
 * @return true nếu > 0, false nếu <= 0.
 */
bool isPositiveNumber(const int& number) { return number > 0; }

/**
 * @brief Kiểm tra định dạng email.
 *
 * Quy tắc:
 *  - Phần trước @: chữ cái, số, dấu chấm (.), gạch dưới (_), dấu cộng (+), gạch ngang (-).
 *  - Phần domain: chỉ chứa chữ, số, dấu chấm (.), gạch ngang (-).
 *  - Phần đuôi: tối thiểu 2 ký tự chữ cái (ví dụ: .com, .vn).
 *
 * Ví dụ hợp lệ:
 *  - user@example.com
 *  - user.name123@example.co.uk
 *
 * @param email Chuỗi email cần kiểm tra.
 * @return true nếu hợp lệ, false nếu không.
 */
bool isValidEmail(const std::string& email) {
  std::regex pattern(
      R"([A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,})");
  return std::regex_match(email, pattern);
}

}  // namespace validation
}  // namespace utils
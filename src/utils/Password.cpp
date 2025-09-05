#include "utils/Password.hpp"

#include <random>
#include <string>

namespace utils {
namespace password {

/**
 * @brief Sinh mật khẩu ngẫu nhiên với độ dài cho trước.
 *
 * Input:
 *   - length: Độ dài mật khẩu cần sinh (số ký tự).
 *
 * Output:
 *   - Trả về chuỗi mật khẩu ngẫu nhiên gồm chữ thường, chữ hoa, số và ký tự đặc biệt.
 *
 * Thủ tục xử lý:
 *   1. Định nghĩa tập ký tự hợp lệ (chữ cái thường, chữ cái hoa, số, ký tự đặc biệt).
 *   2. Khởi tạo bộ sinh số ngẫu nhiên:
 *        - Sử dụng std::random_device để tạo seed.
 *        - Sử dụng std::mt19937 để tạo generator.
 *        - Sử dụng std::uniform_int_distribution để sinh chỉ số ngẫu nhiên trong phạm vi charset.
 *   3. Tạo chuỗi password rỗng, dự trữ trước dung lượng = length.
 *   4. Lặp từ 0 → length-1:
 *        - Sinh ngẫu nhiên một chỉ số từ charset.
 *        - Thêm ký tự tương ứng vào mật khẩu.
 *   5. Trả về mật khẩu đã sinh.
 */
  std::string generateRandomPassword(int length) {
  // Tập ký tự hợp lệ: chữ thường, chữ hoa, số, ký tự đặc biệt
  const std::string charset =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
  // Khởi tạo bộ sinh số ngẫu nhiên
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, charset.length() - 1);
 // Chuỗi kết quả, dự trữ trước dung lượng
  std::string password;
  password.reserve(length);
  // Sinh lần lượt từng ký tự
  for (int i = 0; i < length; ++i) {
    password += charset[distribution(generator)];
  }

  return password;
}

}  // namespace password
}  // namespace utils
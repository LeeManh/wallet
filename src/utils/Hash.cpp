
#include "utils/Hash.hpp"

#include <string>

namespace utils {
namespace hash {

/**
 * @brief Sinh chuỗi băm (hash) từ mật khẩu gốc bằng thuật toán BCrypt.
 *
 * Input:
 *   - password: Mật khẩu gốc cần băm.
 *
 * Output:
 *   - Chuỗi hash tương ứng với mật khẩu đã được mã hoá bằng BCrypt.
 */
std::string generatePasswordHash(const std::string& password) {
  return BCrypt::generateHash(password);
}

/**
 * @brief Xác thực mật khẩu gốc với chuỗi hash bằng BCrypt.
 *
 * Input:
 *   - password: Mật khẩu gốc do người dùng nhập.
 *   - hash: Chuỗi hash đã được lưu trước đó.
 *
 * Output:
 *   - true nếu mật khẩu khớp với hash.
 *   - false nếu không khớp.
 */
bool validatePassword(const std::string& password, const std::string& hash) {
  return BCrypt::validatePassword(password, hash);
}

}  // namespace hash
}  // namespace utils
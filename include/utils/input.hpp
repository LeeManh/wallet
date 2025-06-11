#ifndef INPUT_HPP
#define INPUT_HPP

#include <functional>
#include <string>

#include "utils/Validation.hpp"

namespace utils {
namespace input {

/**
 * Lấy input từ người dùng với validation
 * @param prompt Câu nhắc nhập
 * @param validator Hàm kiểm tra tính hợp lệ
 * @param errorMessage Thông báo lỗi
 * @return Input hợp lệ từ người dùng
 */
std::string getValidatedInput(
    const std::string& prompt,
    const std::function<bool(const std::string&)>& validator,
    const std::string& errorMessage);

}  // namespace input
}  // namespace utils

#endif
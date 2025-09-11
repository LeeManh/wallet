#include "utils/Input.hpp"

#include <iostream>

#include "utils/MessageHandler.hpp"

namespace utils {
namespace input {

/**
 * @brief Lấy dữ liệu nhập từ bàn phím với cơ chế kiểm tra hợp lệ.
 *
 * Input:
 *   - prompt: Chuỗi gợi ý hiển thị cho người dùng trước khi nhập.
 *   - validator: Hàm kiểm tra hợp lệ cho dữ liệu nhập vào 
 *                (trả về true nếu hợp lệ, false nếu không).
 *   - errorMessage: Thông báo lỗi sẽ hiển thị khi dữ liệu nhập không hợp lệ.
 *
 * Output:
 *   - Trả về chuỗi hợp lệ do người dùng nhập vào (được xác thực bằng validator).
 *
 * Thủ tục xử lý:
 *   1. Hiển thị prompt và đọc dữ liệu nhập từ người dùng.
 *   2. Gọi hàm validator để kiểm tra dữ liệu:
 *        - Nếu không hợp lệ → in ra errorMessage và yêu cầu nhập lại.
 *        - Nếu hợp lệ → thoát vòng lặp.
 *   3. Trả về giá trị input hợp lệ cuối cùng.
 */
  std::string getValidatedInput(
    const std::string& prompt,
    const std::function<bool(const std::string&)>& validator,
    const std::string& errorMessage) {
  std::string input;
  do {
    std::cout << prompt;
    std::getline(std::cin, input);

    if (!validator(input)) {
      std::cout << errorMessage << std::endl;
    }
  } while (!validator(input));

  return input;
}

/**
 * @brief Lấy chuỗi nhập từ người dùng với prompt hiển thị trước.
 *
 * Input:
 *   - prompt: Chuỗi gợi ý sẽ được in ra trước khi nhập.
 *
 * Output:
 *   - Trả về chuỗi do người dùng nhập từ bàn phím.
 */
std::string getInput(const std::string& prompt) {
  std::cout << "- " << prompt;
  std::string input;
  std::getline(std::cin, input);
  return input;
}

/**
 * @brief Lấy lựa chọn của người dùng trong một khoảng giá trị hợp lệ.
 *
 * Input:
 *   - min: Giá trị nhỏ nhất mà người dùng có thể chọn.
 *   - max: Giá trị lớn nhất mà người dùng có thể chọn.
 *
 * Output:
 *   - Trả về số nguyên hợp lệ do người dùng nhập.
 *
 * Thủ tục xử lý:
 *   1. Hiển thị lời nhắc yêu cầu người dùng nhập một số.
 *   2. Kiểm tra:
 *        - Nếu nhập không phải số → báo lỗi, xóa trạng thái cin và bỏ qua input lỗi.
 *        - Nếu số nằm ngoài khoảng [min, max] → báo lỗi, yêu cầu nhập lại.
 *   3. Nếu nhập hợp lệ, trả về giá trị đó.
 */
int getChoice(int min, int max) {
  int choice;

  while (true) {
    std::cout << "- Nhập lựa chọn: ";

    // Trường hợp nhập không phải số (vd: ký tự, chuỗi)
    if (!(std::cin >> choice)) {
      utils::MessageHandler::logError(
          "Lựa chọn không hợp lệ! Vui lòng nhập một số.");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Trường hợp nhập số nhưng ngoài khoảng [min, max]
    } else if (choice < min || choice > max) {
      utils::MessageHandler::logError(
          "Lựa chọn không hợp lệ! Vui lòng nhập số từ " + std::to_string(min) +
          " đến " + std::to_string(max) + ".");
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Trường hợp hợp lệ
    } else {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return choice;
    }
  }
}

/**
 * @brief Tạm dừng chương trình cho đến khi người dùng nhấn Enter.
 *
 * Input:
 *   - Không có.
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Chương trình chỉ tiếp tục chạy sau khi người dùng nhấn Enter.
 */
void pauseInput() {
  utils::MessageHandler::logMessage("\nNhấn Enter để tiếp tục...");
  std::cin.ignore();
  std::cin.get();
}

}  // namespace input
}  // namespace utils
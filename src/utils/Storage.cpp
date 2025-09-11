#include "utils/Storage.hpp"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "exceptions/Exception.hpp"

namespace utils {
namespace storage {

/**
 * @brief Đọc dữ liệu JSON từ file.
 *
 * Input:
 *   - path: Đường dẫn tới file JSON cần đọc.
 *
 * Output:
 *   - Trả về đối tượng JSON đã parse.
 *   - Nếu file không mở được, ném StorageException.
 *   - Nếu dữ liệu trong file không hợp lệ, ném std::exception.
 *
 * Thủ tục xử lý:
 *   1. Mở file theo đường dẫn truyền vào.
 *   2. Nếu không mở được, ném StorageException với thông báo lỗi.
 *   3. Thử parse dữ liệu từ file vào đối tượng JSON:
 *        - Nếu parse thành công, lưu vào biến data.
 *        - Nếu parse thất bại, ném ngoại lệ std::exception.
 *   4. Đóng file sau khi đọc xong.
 *   5. Trả về dữ liệu JSON.
 */
  json readJsonFile(const std::string& path) {
  json data = json::array();  // Default to empty array
  std::ifstream file(path);

  if (!file.is_open())
    throw exceptions::StorageException("Không thể mở file: " + path);

  try {
    file >> data;
  } catch (const std::exception& e) {
    throw e;
  }

  file.close();
  return data;
}

/**
 * @brief Ghi dữ liệu JSON ra file.
 *
 * Input:
 *   - path: Đường dẫn tới file JSON cần ghi.
 *   - data: Đối tượng JSON cần ghi ra file.
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Nếu không ghi được file, ném StorageException.
 *
 * Thủ tục xử lý:
 *   1. Mở file theo đường dẫn truyền vào với chế độ ghi.
 *   2. Nếu không mở được file, ném StorageException.
 *   3. Ghi dữ liệu JSON ra file với định dạng thụt dòng (indent = 4).
 *   4. Đóng file sau khi ghi xong.
 */
bool writeJsonFile(const std::string& path, const json& data) {
  try {
    // Mở file với mode binary để tránh vấn đề với line endings
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
      throw exceptions::StorageException(std::string("Không thể mở file ") +
                                         path + " để ghi");
    }

    // Ghi dữ liệu với định dạng đẹp
    file << std::setw(2) << data << std::endl;
    file.close();
    return true;
  } catch (const std::exception& e) {
    throw e;
  }
}

/**
 * @brief Kiểm tra sự tồn tại của file hoặc thư mục tại đường dẫn cho trước.
 *
 * Input:
 *   - path: Đường dẫn file hoặc thư mục cần kiểm tra.
 *
 * Output:
 *   - true  nếu tồn tại.
 *   - false nếu không tồn tại.
 */
bool fileExists(const std::string& path) {
  return std::filesystem::exists(path);
}

/**
 * @brief Đảm bảo thư mục tại đường dẫn cho trước tồn tại.
 *
 * Input:
 *   - path: Đường dẫn thư mục cần kiểm tra/tạo.
 *
 * Output:
 *   - true nếu thư mục đã tồn tại hoặc tạo mới thành công.
 *   - Ném ngoại lệ (std::exception) nếu có lỗi khi tạo thư mục.
 */
bool ensureDirectoryExists(const std::string& path) {
  try {
    std::filesystem::create_directories(path);
    return true;
  } catch (const std::exception& e) {
    throw e;
  }
}

/**
 * @brief Tạo file JSON tại đường dẫn chỉ định nếu chưa tồn tại.
 *
 * Input:
 *   - path: Đường dẫn file cần tạo.
 *   - defaultValue: Giá trị mặc định (JSON) sẽ được ghi vào file nếu file chưa tồn tại.
 *
 * Output:
 *   - true nếu file tồn tại hoặc tạo mới thành công.
 *   - Ném ngoại lệ (std::exception) nếu xảy ra lỗi trong quá trình tạo file hoặc ghi dữ liệu.
 */
bool createFile(const std::string& path, const json& defaultValue) {
  try {
    std::filesystem::path filePath(path);

    // Tạo thư mục cha nếu chưa tồn tại
    std::filesystem::create_directories(filePath.parent_path());

    // Kiểm tra xem file đã tồn tại chưa
    if (std::filesystem::exists(filePath)) {
      return true;
    }

    // Tạo file mới với giá trị mặc định
    return writeJsonFile(path, defaultValue);
  } catch (const std::exception& e) {
    throw e;
  }
}

/**
 * @brief Lấy ID kế tiếp cho người dùng mới.
 *
 * Input:
 *   - users: Mảng JSON chứa danh sách người dùng (mỗi user có trường "id").
 *
 * Output:
 *   - Trả về ID mới cho người dùng kế tiếp.
 *     + Nếu mảng rỗng -> trả về 1 (ID bắt đầu từ 1).
 *     + Nếu không rỗng -> lấy "id" của phần tử cuối cùng và cộng thêm 1.
 *
 * Lưu ý:
 *   - Giả định mảng users được sắp xếp theo thứ tự tăng dần theo "id".
 */
int getNextUserId(const json& users) {
  // Nếu chưa có user nào -> ID bắt đầu từ 1
  if (users.empty()) return 1;
  // Lấy id của user cuối cùng và cộng thêm 1
  return users.back()["id"].get<int>() + 1;
}

/**
 * @brief Lấy ID kế tiếp cho một ví mới.
 *
 * Input:
 *   - Danh sách các ví (JSON array).
 *
 * Output:
 *   - Trả về ID mới cho ví tiếp theo.
 *     + Nếu danh sách trống -> trả về 1.
 *     + Nếu có -> lấy "id" của ví cuối cùng và cộng thêm 1.
 *
 * Lưu ý:
 *   - Hàm giả định mảng wallets được sắp xếp theo "id" tăng dần.
 *   - Nếu dữ liệu không được sắp xếp, kết quả có thể sai.
 */
int getNextWalletId(const json& wallets) {
  // Nếu chưa có ví nào -> ID bắt đầu từ 1
  if (wallets.empty()) return 1;
  // Lấy id của ví cuối cùng và cộng thêm 1
  return wallets.back()["id"].get<int>() + 1;
}

/**
 * @brief Lấy ID kế tiếp cho một giao dịch mới.
 *
 * Input:
 *   - Đọc danh sách các transaction từ file "data/transactions.json".
 *
 * Output:
 *   - Trả về ID mới cho transaction tiếp theo.
 *     + Nếu file trống hoặc không có transaction -> trả về 1.
 *     + Nếu có -> lấy "id" của transaction cuối cùng và cộng thêm 1.
 *
 * Lưu ý:
 *   - Hàm giả định mảng transactions trong file được sắp xếp theo "id" tăng dần.
 *   - Nếu dữ liệu không được sắp xếp, kết quả có thể bị sai.
 */
int getNextTransactionId() {
  // Đọc toàn bộ danh sách giao dịch từ file JSON
  json transactions = readJsonFile("data/transactions.json");
   // Nếu chưa có giao dịch nào -> ID bắt đầu từ 1
  if (transactions.empty()) return 1;
  // Lấy id của giao dịch cuối cùng và cộng thêm 1
  return transactions.back()["id"].get<int>() + 1;
}

}  // namespace storage
}  // namespace utils
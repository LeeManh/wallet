#pragma once

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace utils {
namespace storage {
// Đọc JSON từ file
json readJsonFile(const std::string& path);

// Ghi JSON vào file
bool writeJsonFile(const std::string& path, const json& data);

// Kiểm tra file có tồn tại không
bool fileExists(const std::string& path);

// Tạo thư mục nếu chưa tồn tại
bool ensureDirectoryExists(const std::string& path);

// Create file
bool createFile(const std::string& path,
                const json& defaultValue = json::array());

// Lấy ID tiếp theo
int getNextUserId(const json& users);
int getNextWalletId(const json& wallets);
int getNextOtpId(const json& otps);

}  // namespace storage
}  // namespace utils

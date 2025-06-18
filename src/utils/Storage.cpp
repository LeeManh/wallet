#include "utils/Storage.hpp"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "exceptions/Exception.hpp"

namespace utils {
namespace storage {

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

bool fileExists(const std::string& path) {
  return std::filesystem::exists(path);
}

bool ensureDirectoryExists(const std::string& path) {
  try {
    std::filesystem::create_directories(path);
    return true;
  } catch (const std::exception& e) {
    throw e;
  }
}

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

int getNextUserId(const json& users) {
  if (users.empty()) return 1;

  return users.back()["id"].get<int>() + 1;
}

int getNextWalletId(const json& wallets) {
  if (wallets.empty()) return 1;

  int maxId = 0;
  for (const auto& wallet : wallets) {
    if (wallet["id"].get<int>() > maxId) {
      maxId = wallet["id"].get<int>();
    }
  }
  return maxId + 1;
}

}  // namespace storage
}  // namespace utils
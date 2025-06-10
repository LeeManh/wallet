
#include "utils/storage.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace utils {
namespace storage {

json readJsonFile(const std::string& path) {
  json data = json::array();  // Default to empty array
  std::ifstream file(path);

  if (file.is_open()) {
    try {
      file >> data;
    } catch (const std::exception& e) {
      std::cerr << "Lỗi đọc file " << path << ": " << e.what() << std::endl;
    }
    file.close();
  } else {
    std::cerr << "Không thể mở file " << path << std::endl;
  }

  return data;
}

bool writeJsonFile(const std::string& path, const json& data) {
  // Đảm bảo thư mục tồn tại
  std::filesystem::path filePath(path);
  if (!ensureDirectoryExists(filePath.parent_path().string())) {
    return false;
  }

  std::ofstream file(path);
  if (!file.is_open()) {
    std::cerr << "Không thể mở file " << path << " để ghi" << std::endl;
    return false;
  }

  try {
    file << std::setw(2) << data << std::endl;
    file.close();
    return true;
  } catch (const std::exception& e) {
    std::cerr << "Lỗi ghi file " << path << ": " << e.what() << std::endl;
    return false;
  }
}

bool fileExists(const std::string& path) {
  return std::filesystem::exists(path);
}

bool ensureDirectoryExists(const std::string& path) {
  if (path.empty()) return true;
  return std::filesystem::create_directories(path);
}

}  // namespace storage
}  // namespace utils
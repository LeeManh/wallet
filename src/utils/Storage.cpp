
#include "utils/Storage.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace utils {
namespace storage {

std::string getPathSeparator() {
#ifdef _WIN32
  return "\\";
#else
  return "/";
#endif
}

std::string joinPaths(const std::string& path1, const std::string& path2) {
  return path1 + getPathSeparator() + path2;
}

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
  try {
    // Đảm bảo thư mục tồn tại
    std::filesystem::path filePath(path);
    std::filesystem::create_directories(filePath.parent_path());

    // Mở file với mode binary để tránh vấn đề với line endings
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
      std::cerr << "Không thể mở file " << path << " để ghi" << std::endl;
      return false;
    }

    // Ghi dữ liệu với định dạng đẹp
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
  try {
    return std::filesystem::create_directories(path);
  } catch (const std::exception& e) {
    std::cerr << "Error creating directory: " << e.what() << std::endl;
    return false;
  }
}

int getNextUserId(const json& users) {
  if (users.empty()) return 1;

  return users.back()["id"].get<int>() + 1;
}

}  // namespace storage
}  // namespace utils
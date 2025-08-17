#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "utils/Storage.hpp"

namespace services {

class CredentialBackup {
 public:
  // usersFile: DATA_DIR/users.json (mặc định)
  // backupDir : BACKUP_DIR (mặc định)
  // loginFile : DATA_DIR/login_logs.json (mặc định) – nơi lưu lịch sử đăng nhập
  explicit CredentialBackup(std::string usersFile = {},
                            std::string backupDir = {},
                            std::string loginFile = {});

  // Tạo snapshot: backupDir/users-YYYYMMDD-HHMMSS.json
  // Trả về đường dẫn file đã tạo (rỗng nếu lỗi)
  std::string backup() const;

  // Phục hồi người dùng từ một file backup
  // reason: mô tả lỗi (nếu có)
  bool restore(const std::string& backupFile, std::string* reason = nullptr) const;

  // Xuất danh sách tài khoản ẩn mật khẩu
  bool exportMasked(const std::string& outFile) const;

  // ⬇️ HÀM MỚI: Xuất lịch sử đăng nhập của một user ra JSON
  // Trả về true nếu ghi file thành công; reason chứa mô tả lỗi nếu có.
  bool exportUserLoginHistory(int userId,
                              const std::string& outFile,
                              std::string* reason = nullptr) const;

 private:
  nlohmann::json readAll() const;                    // đọc users.json
  bool writeAll(const nlohmann::json& arr) const;    // ghi users.json

  std::string usersFile_;
  std::string backupDir_;
  std::string loginFile_; // file chứa log đăng nhập
};

}  // namespace services

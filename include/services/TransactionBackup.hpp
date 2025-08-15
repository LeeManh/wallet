#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace services {

// Chỉ phụ trách BACKUP/RESTORE dữ liệu giao dịch (transactions.json)
class TransactionBackup {
 public:
  explicit TransactionBackup(std::string dataFile = "data/transactions.json",
                             std::string backupDir = "backup");

  // Tạo file backup: backup/transactions-YYYYMMDD-HHMMSS.json
  // Trả về đường dẫn file (rỗng nếu lỗi)
  std::string backup() const;

  // Khôi phục từ file backup vào data/transactions.json
  // Nếu lỗi, trả về false và điền reason (nếu không null)
  bool restore(const std::string& backupFile, std::string* reason = nullptr) const;

  // Xuất lịch sử của 1 ví ra file riêng (JSON array)
  bool exportWallet(int walletId, const std::string& outFile) const;

 private:
  std::string dataFile_;
  std::string backupDir_;

  // Helpers
  static bool ensureDir(const std::string& path);
  json readAll() const;
  bool writeAll(const json& arr) const;
};

}  // namespace services

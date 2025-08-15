#include "services/TransactionBackup.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>

#ifdef _WIN32
  #include <direct.h>
  #include <sys/stat.h>
#else
  #include <sys/stat.h>
  #include <sys/types.h>
#endif

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif
#ifndef BACKUP_DIR
#define BACKUP_DIR "backup"
#endif

using services::TransactionBackup;

TransactionBackup::TransactionBackup(std::string dataFile, std::string backupDir)
    : dataFile_(std::move(dataFile)), backupDir_(std::move(backupDir)) {
  if (dataFile_.empty())  dataFile_  = std::string(DATA_DIR) + "/transactions.json";
  if (backupDir_.empty()) backupDir_ = std::string(BACKUP_DIR);
}

bool TransactionBackup::ensureDir(const std::string& path) {
#ifdef _WIN32
  struct _stat st{};
  if (_stat(path.c_str(), &st) == 0 && (st.st_mode & _S_IFDIR)) return true;
  return _mkdir(path.c_str()) == 0;
#else
  struct stat st{};
  if (stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) return true;
  return mkdir(path.c_str(), 0755) == 0;
#endif
}

json TransactionBackup::readAll() const {
  json arr = utils::storage::readJsonFile(dataFile_);
  if (!arr.is_array()) return json::array();
  return arr;
}

bool TransactionBackup::writeAll(const json& arr) const {
  return utils::storage::writeJsonFile(dataFile_, arr);
}

std::string TransactionBackup::backup() const {
  std::time_t now = std::time(nullptr);
  std::tm* tmv = std::localtime(&now);
  std::ostringstream name;
  name << backupDir_ << "/transactions-";
  name << std::put_time(tmv, "%Y%m%d-%H%M%S") << ".json";

  ensureDir(backupDir_);
  json all = readAll();
  if (!utils::storage::writeJsonFile(name.str(), all)) return {};
  return name.str();
}

bool TransactionBackup::restore(const std::string& backupFile, std::string* reason) const {
  json arr = utils::storage::readJsonFile(backupFile);
  if (!arr.is_array()) {
    if (reason) *reason = "Backup không phải mảng JSON hợp lệ.";
    return false;
  }
  for (const auto& tx : arr) {
    if (!tx.is_object() ||
        !tx.contains("id") ||
        !tx.contains("sourceWalletId") ||
        !tx.contains("destinationWalletId") ||
        !tx.contains("amount") ||
        !tx.contains("status")) {
      if (reason) *reason = "Thiếu trường bắt buộc trong một giao dịch.";
      return false;
    }
  }
  if (!writeAll(arr)) {
    if (reason) *reason = "Không thể ghi đè transactions.json.";
    return false;
  }
  return true;
}

bool TransactionBackup::exportWallet(int walletId, const std::string& outFile) const {
  json all = readAll();
  json arr = json::array();
  for (const auto& tx : all) {
    if (!tx.is_object()) continue;
    int src = tx.value("sourceWalletId", -1);
    int dst = tx.value("destinationWalletId", -1);
    if (src == walletId || dst == walletId) arr.push_back(tx);
  }
  return utils::storage::writeJsonFile(outFile, arr);
}

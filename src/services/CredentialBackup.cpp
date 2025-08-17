#include "services/CredentialBackup.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

#ifndef BACKUP_DIR
#define BACKUP_DIR "backup"
#endif

using nlohmann::json;

namespace services {

static std::string nowStamp() {
  std::time_t t = std::time(nullptr);
  std::tm tm{};
#ifdef _WIN32
  localtime_s(&tm, &t);
#else
  localtime_r(&t, &tm);
#endif
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y%m%d-%H%M%S");
  return oss.str();
}

CredentialBackup::CredentialBackup(std::string usersFile,
                                   std::string backupDir,
                                   std::string loginFile)
    : usersFile_(usersFile.empty() ? std::string(DATA_DIR) + "/users.json" : usersFile),
      backupDir_(backupDir.empty() ? std::string(BACKUP_DIR) : backupDir),
      loginFile_(loginFile.empty() ? std::string(DATA_DIR) + "/login_logs.json" : loginFile) {}

json CredentialBackup::readAll() const {
  try {
    return utils::storage::readJsonFile(usersFile_);
  } catch (...) {
    return json::array();
  }
}

bool CredentialBackup::writeAll(const json& arr) const {
  return utils::storage::writeJsonFile(usersFile_, arr);
}

std::string CredentialBackup::backup() const {
  try {
    auto arr = readAll();
    if (!arr.is_array()) arr = json::array();
    std::string out = backupDir_ + "/users-" + nowStamp() + ".json";
    if (utils::storage::writeJsonFile(out, arr)) return out;
  } catch (...) {}
  return {};
}

bool CredentialBackup::restore(const std::string& backupFile, std::string* reason) const {
  try {
    auto arr = utils::storage::readJsonFile(backupFile);
    if (!arr.is_array()) {
      if (reason) *reason = "File backup không phải mảng JSON.";
      return false;
    }
    if (!writeAll(arr)) {
      if (reason) *reason = "Ghi users.json thất bại.";
      return false;
    }
    return true;
  } catch (const std::exception& e) {
    if (reason) *reason = e.what();
    return false;
  }
}

bool CredentialBackup::exportMasked(const std::string& outFile) const {
  try {
    auto arr = readAll();
    if (!arr.is_array()) arr = json::array();
    // Ẩn mật khẩu (nếu có)
    for (auto& u : arr) {
      if (u.contains("password")) u["password"] = "***";
      if (u.contains("hash"))     u["hash"]     = "***";
    }
    return utils::storage::writeJsonFile(outFile, arr);
  } catch (...) {
    return false;
  }
}

bool CredentialBackup::exportUserLoginHistory(int userId,
                                              const std::string& outFile,
                                              std::string* reason) const {
  try {
    // Định dạng mặc định của file log đăng nhập:
    // [
    //   {"userId": 1, "time": 1712740212, "ip": "x.x.x.x", "status":"success"},
    //   ...
    // ]
    auto logs = utils::storage::readJsonFile(loginFile_);
    if (!logs.is_array()) {
      if (reason) *reason = "File log không phải mảng JSON.";
      return false;
    }

    json out = json::array();
    for (const auto& item : logs) {
      if (!item.is_object()) continue;
      if (item.value("userId", -1) == userId) out.push_back(item);
    }

    if (out.empty()) {
      // Không coi là lỗi – vẫn xuất một mảng rỗng để người dùng biết
      // user chưa có lịch sử đăng nhập.
    }
    if (!utils::storage::writeJsonFile(outFile, out)) {
      if (reason) *reason = "Ghi file xuất thất bại.";
      return false;
    }
    return true;
  } catch (const std::exception& e) {
    if (reason) *reason = e.what();
    return false;
  }
}

} // namespace services

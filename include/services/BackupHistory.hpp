#pragma once
#include <string>
#include <vector>

namespace services {

struct BackupRecord {
    std::string timestamp;
    std::string directory;
};

class BackupHistory {
public:
    // Ghi log backup
    static void logBackup(const std::string &timestamp, const std::string &dir);

    // Lấy toàn bộ lịch sử backup
    static std::vector<BackupRecord> getHistory();

    // In lịch sử backup ra console
    static void printAll();
};

} // namespace services

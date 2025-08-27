#include "services/BackupHistory.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>

namespace services {

static const std::string HISTORY_FILE = "backups/history.log";

// Ghi một lần backup mới vào history.log
void BackupHistory::logBackup(const std::string &timestamp, const std::string &dir) {
    std::ofstream out(HISTORY_FILE, std::ios::app);
    if (out.is_open()) {
        out << timestamp << "|" << dir << "\n";
    }
}

// Đọc toàn bộ lịch sử backup từ file
std::vector<BackupRecord> BackupHistory::getHistory() {
    std::vector<BackupRecord> history;
    std::ifstream in(HISTORY_FILE);
    if (!in.is_open()) return history;

    std::string line;
    while (std::getline(in, line)) {
        size_t pos = line.find('|');
        if (pos != std::string::npos) {
            BackupRecord rec;
            rec.timestamp = line.substr(0, pos);
            rec.directory = line.substr(pos + 1);
            history.push_back(rec);
        }
    }
    return history;
}

// In toàn bộ lịch sử backup ra console
void BackupHistory::printAll() {
    auto history = getHistory();
    if (history.empty()) {
        std::cout << "Chưa có bản backup nào.\n";
        return;
    }

    std::cout << "\n+-----+---------------------+-------------------------+\n";
    std::cout << "| STT |     Thời gian       |        Thư mục          |\n";
    std::cout << "+-----+---------------------+-------------------------+\n";

    int i = 1;
    for (const auto &rec : history) {
        std::cout << "| " << std::setw(3) << i++ << " | "
                  << std::setw(19) << rec.timestamp << " | "
                  << std::setw(23) << rec.directory << " |\n";
    }
    std::cout << "+-----+---------------------+-------------------------+\n";
}

} // namespace services

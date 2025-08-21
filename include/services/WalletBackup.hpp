#pragma once
#include <string>

namespace services {

class WalletBackup {
public:
    // Sao lưu toàn bộ ví/số dư ra file JSON đích
    static void exportToFile(const std::string& path);
    // Phục hồi ví/số dư từ file JSON nguồn
    static void importFromFile(const std::string& path);
};

} // namespace services

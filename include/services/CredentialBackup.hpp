#pragma once
#include <string>

namespace services {

class CredentialBackup {
public:
    // Xuất dữ liệu users.json ra file backup
    static void exportToFile(const std::string& outPath);

    // Nhập dữ liệu từ file backup vào users.json
    static void importFromFile(const std::string& inPath);
};

}

#pragma once
#include <string>

namespace services {

class TransactionBackup {
public:
    // Xuất dữ liệu transactions.json ra file backup
    static void exportToFile(const std::string& outPath);

    // Nhập dữ liệu từ file backup vào transactions.json
    static void importFromFile(const std::string& inPath);
};

}
#include "services/TransactionBackup.hpp"
#include "utils/MessageHandler.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <algorithm>

namespace fs = std::filesystem;

namespace {
    fs::path txDataPath() { return fs::path(DATA_DIR) / "transactions.json"; }

    void ensureParent(const fs::path& p) {
        if (p.has_parent_path()) fs::create_directories(p.parent_path());
    }

    std::string normalizePath(const std::string& raw) {
        std::string path = raw;
        if (!path.empty() && path.front() == '"' && path.back() == '"') {
            path = path.substr(1, path.size() - 2);
        }
        std::replace(path.begin(), path.end(), '\\', '/');
        return path;
    }

    bool validateJsonFile(const fs::path& p, std::string& reason) {
        try {
            std::ifstream ifs(p, std::ios::in | std::ios::binary);
            if (!ifs.is_open()) { reason = "Không mở được file: " + p.string(); return false; }
            nlohmann::json j; ifs >> j;
            return true;
        } catch (const std::exception& e) {
            reason = e.what(); return false;
        }
    }
}

namespace services {

void TransactionBackup::exportToFile(const std::string& outPath) {
    const fs::path src = txDataPath();
    const fs::path dst = outPath;
    ensureParent(dst);

    if (!fs::exists(src)) {
        std::ofstream ofs(dst); ofs << "[]";
        utils::MessageHandler::logMessage("transactions.json không tồn tại; đã tạo file rỗng -> " + dst.string());
        return;
    }

    fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
    utils::MessageHandler::logMessage("Đã sao lưu transactions -> " + dst.string());
}

void TransactionBackup::importFromFile(const std::string& inPath) {
    const fs::path src = normalizePath(inPath);
    const fs::path dst = txDataPath();

    if (!fs::exists(src)) {
        utils::MessageHandler::logError("Không thấy file: " + src.string());
        return;
    }

    std::string why;
    if (!validateJsonFile(src, why)) {
        utils::MessageHandler::logError("File JSON không hợp lệ: " + why);
        return;
    }

    ensureParent(dst);
    if (fs::exists(dst)) {
        fs::copy_file(dst, dst.string() + ".bak", fs::copy_options::overwrite_existing);
    }

    fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
    utils::MessageHandler::logMessage("✅ Đã phục hồi transactions <- " + src.string());
}

}

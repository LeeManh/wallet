#include "services/WalletBackup.hpp"
#include "utils/MessageHandler.hpp"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

namespace {
    fs::path walletsDataPath(){ return fs::path(DATA_DIR) / "wallets.json"; }
    void ensureParent(const fs::path& p){ if (p.has_parent_path()) fs::create_directories(p.parent_path()); }
    bool validateJson(const fs::path& p, std::string& why){
        try { std::ifstream ifs(p); if(!ifs) { why="Không mở được: "+p.string(); return false; }
              nlohmann::json j; ifs >> j; return true; }
        catch (const std::exception& e){ why = e.what(); return false; }
    }
}

namespace services {

void WalletBackup::exportToFile(const std::string& outPath) {
    fs::path src = walletsDataPath(), dst = outPath;
    ensureParent(dst);
    if (!fs::exists(src)) { std::ofstream(dst) << "[]"; 
        utils::MessageHandler::logMessage("wallets.json không tồn tại; đã tạo file rỗng -> " + dst.string());
        return;
    }
    fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
    utils::MessageHandler::logMessage("Đã sao lưu wallets -> " + dst.string());
}

void WalletBackup::importFromFile(const std::string& inPath) {
    fs::path src = inPath, dst = walletsDataPath();
    if (!fs::exists(src)) { utils::MessageHandler::logError("Không thấy file: " + src.string()); return; }
    std::string why; if (!validateJson(src, why)) {
        utils::MessageHandler::logError("File JSON không hợp lệ: " + why); return;
    }
    ensureParent(dst);
    if (fs::exists(dst)) fs::copy_file(dst, dst.string()+".bak", fs::copy_options::overwrite_existing);
    fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
    utils::MessageHandler::logMessage("Đã phục hồi wallets <- " + src.string());
}

}

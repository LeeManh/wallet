#include "controllers/AuthController.hpp"
#include "services/UserService.hpp"
#include "utils/MessageHandler.hpp"
#include "utils/Format.hpp"
#include "models/User.hpp"

/**
 * @brief Hiển thị thông tin cá nhân của người dùng theo dạng bảng 2 cột.
 *
 * Hàm này trình bày thông tin cá nhân và vai trò/ví của người dùng dưới dạng
 * bảng ASCII có khung, gồm 2 phần:
 *   - 👤 Thông tin cơ bản (họ tên, email, tên đăng nhập, user ID).
 *   - 🎭 Vai trò & Ví (vai trò, số dư ví).
 *
 * Input:
 *   - fullName: họ và tên của người dùng.
 *   - email: địa chỉ email của người dùng.
 *   - username: tên đăng nhập.
 *   - userId: mã định danh người dùng (ID).
 *   - role: vai trò (ví dụ: Admin, Customer).
 *   - walletBalance: số dư ví (dạng điểm).
 *
 * Output:
 *   - Không trả về giá trị. Thông tin được in ra console bằng
 *     utils::MessageHandler::logMessage().
 */
void displayUserInfo(const std::string& fullName,
                     const std::string& email,
                     const std::string& username,
                     int userId,
                     const std::string& role,
                     double walletBalance) {
    utils::MessageHandler::logMessage("\n👤 Thông tin cơ bản");
    utils::MessageHandler::logMessage(
        "+----------------------+--------------------------------+");

    utils::MessageHandler::logMessage(
        "| " + utils::format::padRight("Họ và tên", 20) + " | " +
        utils::format::padRight(fullName, 30) + " |");
    utils::MessageHandler::logMessage(
        "+----------------------+--------------------------------+");
    utils::MessageHandler::logMessage(
        "| " + utils::format::padRight("Email", 20) + " | " +
        utils::format::padRight(email, 30) + " |");
    utils::MessageHandler::logMessage(
        "+----------------------+--------------------------------+");

    utils::MessageHandler::logMessage(
        "| " + utils::format::padRight("Tên đăng nhập", 20) + " | " +
        utils::format::padRight(username, 30) + " |");
    utils::MessageHandler::logMessage(
        "+----------------------+--------------------------------+");

    utils::MessageHandler::logMessage(
        "| " + utils::format::padRight("User ID", 20) + " | " +
        utils::format::padRight(std::to_string(userId), 30) + " |");
    utils::MessageHandler::logMessage(
        "+----------------------+--------------------------------+");

    // ========== BẢNG 2: Vai trò & Ví ==========
    utils::MessageHandler::logMessage("\n🎭 Vai trò & Ví");
    utils::MessageHandler::logMessage(
        "+----------------------+--------------------------------+");

    utils::MessageHandler::logMessage(
        "| " + utils::format::padRight("Vai trò", 20) + " | " +
        utils::format::padRight(role, 29) + " |");
    utils::MessageHandler::logMessage(
        "+----------------------+--------------------------------+");

    std::string balanceText =
        "💰 " + utils::format::formatPoint(walletBalance) + " điểm";
    utils::MessageHandler::logMessage(
        "| " + utils::format::padRight("Số dư ví", 20) + " | " +
        utils::format::padRight(balanceText, 29) + " |");
    utils::MessageHandler::logMessage(
        "+----------------------+--------------------------------+");
}
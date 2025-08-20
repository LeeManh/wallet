#include <vector>
#include <sstream>

#include "controllers/LogController.hpp"

#include "utils/MessageHandler.hpp"
#include "utils/Format.hpp"
#include "utils/ExceptionHandler.hpp"

#include "models/User.hpp"
#include "models/Wallet.hpp"

#include "enums/Enums.hpp"

#include "services/UserService.hpp"
#include "services/WalletService.hpp"

namespace controllers
{
        /**
     * @brief In danh sách người dùng ra log dưới dạng bảng.
     *
     * Input:
     *   - users: Danh sách đối tượng User cần in.
     *   - userInfo: Danh sách các loại thông tin cột cần hiển thị (ví dụ: ID, USERNAME, EMAIL...).
     *
     * Output:
     *   - Không trả về giá trị.
     *   - Kết quả được in ra log dưới dạng bảng với tiêu đề và đường viền.
     *
     * Thủ tục xử lý:
     *   1. Tạo đường viền trên và tiêu đề bảng dựa trên danh sách cột userInfo.
     *   2. In đường viền và tiêu đề ra log.
     *   3. Duyệt qua từng người dùng trong users:
     *        - Lấy thông tin từng cột từ user.
     *        - Canh chỉnh độ rộng cột và ghép thành một dòng.
     *        - In dòng đó ra log.
     *   4. In đường viền dưới bảng.
     *   5. Nếu xảy ra lỗi, gọi ExceptionHandler để xử lý.
     */
    void LogController::printList(std::vector<models::User> users,
                                    std::vector<enums::UserInfo> userInfo) {
        try {
            std::string borderLine = "+";
            std::string header = "|";

            for(const auto& info : userInfo) {
                int width = utils::format::getCellSize(info);
                header += " " + utils::format::formatCell(utils::format::to_string(info), width) + "|";
                borderLine += "-" + utils::format::formatBorder(width) + "+";
            }

            utils::MessageHandler::logMessage(borderLine);
            utils::MessageHandler::logMessage(header);
            utils::MessageHandler::logMessage(borderLine);

            for (const auto& user : users) {
                std::ostringstream oss;
                for(const auto& info : userInfo) {
                    int width = utils::format::getCellSize(info);
                    std::string cellContent = services::UserService::getUserInfo(user, info);
                    oss << "| " << utils::format::formatCell(cellContent, width);
                }
                utils::MessageHandler::logMessage(oss.str() + "|");
            }

            utils::MessageHandler::logMessage(borderLine);

        } catch (const std::exception& e) {
            utils::ExceptionHandler::handleException(e);
        }
    }
    
    void LogController::printList(models::User user,
                                    std::vector<enums::UserInfo> userInfo) {
        try {
            std::string borderLine = "+";
            std::string header = "|";

            for(const auto& info : userInfo) {
                int width = utils::format::getCellSize(info);
                header += " " + utils::format::formatCell(utils::format::to_string(info), width) + "|";
                borderLine += "-" + utils::format::formatBorder(width) + "+";
            }

            utils::MessageHandler::logMessage(borderLine);
            utils::MessageHandler::logMessage(header);
            utils::MessageHandler::logMessage(borderLine);

            std::ostringstream oss;
            for(const auto& info : userInfo) {
                int width = utils::format::getCellSize(info);
                std::string cellContent = services::UserService::getUserInfo(user, info);
                oss << "| " << utils::format::formatCell(cellContent, width);
            }
            utils::MessageHandler::logMessage(oss.str() + "|");
            

            utils::MessageHandler::logMessage(borderLine);

        } catch (const std::exception& e) {
            utils::ExceptionHandler::handleException(e);
        }
    }

    void LogController::printList(std::vector<models::Wallet> wallets,
                                    std::vector<enums::WalletInfo> walletInfo) {
        try {
            std::string borderLine = "+";
            std::string header = "|";

            for(const auto& info : walletInfo) {
                int width = utils::format::getCellSize(info);
                header += " " + utils::format::formatCell(utils::format::to_string(info), width) + "|";
                borderLine += "-" + utils::format::formatBorder(width) + "+";
            }

            utils::MessageHandler::logMessage(borderLine);
            utils::MessageHandler::logMessage(header);
            utils::MessageHandler::logMessage(borderLine);

            for (const auto& wallet : wallets) {
                std::ostringstream oss;
                for(const auto& info : walletInfo) {
                    int width = utils::format::getCellSize(info);
                    std::string cellContent = services::WalletService::getWalletInfo(wallet, info);
                    oss << "| " << utils::format::formatCell(cellContent, width);
                }
                utils::MessageHandler::logMessage(oss.str() + "|");
            }

            utils::MessageHandler::logMessage(borderLine);

        } catch (const std::exception& e) {
            utils::ExceptionHandler::handleException(e);
        }
    }
    void LogController::printList(models::Wallet wallet,
                                    std::vector<enums::WalletInfo> walletInfo) {
        try {
            std::string borderLine = "+";
            std::string header = "|";

            for(const auto& info : walletInfo) {
                int width = utils::format::getCellSize(info);
                header += " " + utils::format::formatCell(utils::format::to_string(info), width) + "|";
                borderLine += "-" + utils::format::formatBorder(width) + "+";
            }

            utils::MessageHandler::logMessage(borderLine);
            utils::MessageHandler::logMessage(header);
            utils::MessageHandler::logMessage(borderLine);
            std::ostringstream oss;
            for(const auto& info : walletInfo) {
                int width = utils::format::getCellSize(info);
                std::string cellContent = services::WalletService::getWalletInfo(wallet, info);
                oss << "| " << utils::format::formatCell(cellContent, width);
            }
            utils::MessageHandler::logMessage(oss.str() + "|");
            utils::MessageHandler::logMessage(borderLine);

        } catch (const std::exception& e) {
            utils::ExceptionHandler::handleException(e);
        }
    }

} // namespace controllers

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
     * Hàm này tạo và in ra một bảng định dạng đẹp mắt của các đối tượng
     * `models::User`. Bảng bao gồm đường viền, tiêu đề cột và dữ liệu
     * được căn chỉnh.
     *
     * @param users Danh sách các đối tượng `models::User` cần in.
     * @param userInfo Danh sách các loại thông tin (`enums::UserInfo`)
     * cần hiển thị làm cột.
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
    
    /**
     * @brief In thông tin một người dùng duy nhất ra log dưới dạng bảng.
     *
     * Hàm này tương tự như phiên bản vector, nhưng chỉ xử lý một đối tượng
     * `models::User` duy nhất, in ra một bảng một hàng.
     *
     * @param user Đối tượng `models::User` duy nhất cần in.
     * @param userInfo Danh sách các loại thông tin (`enums::UserInfo`)
     * cần hiển thị làm cột.
     */
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

    /**
     * @brief In danh sách ví ra log dưới dạng bảng.
     *
     * Hàm này tạo và in ra một bảng định dạng đẹp mắt của các đối tượng
     * `models::Wallet`. Bảng bao gồm đường viền, tiêu đề cột và dữ liệu
     * được căn chỉnh.
     *
     * @param wallets Danh sách các đối tượng `models::Wallet` cần in.
     * @param walletInfo Danh sách các loại thông tin (`enums::WalletInfo`)
     * cần hiển thị làm cột.
     */
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

    /**
     * @brief In thông tin một ví duy nhất ra log dưới dạng bảng.
     *
     * Hàm này tương tự như phiên bản vector, nhưng chỉ xử lý một đối tượng
     * `models::Wallet` duy nhất, in ra một bảng một hàng.
     *
     * @param wallet Đối tượng `models::Wallet` duy nhất cần in.
     * @param walletInfo Danh sách các loại thông tin (`enums::WalletInfo`)
     * cần hiển thị làm cột.
     */
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
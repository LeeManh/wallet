#include <vector>
#include <sstream>

#include "controllers/LogController.hpp"

#include "utils/MessageHandler.hpp"
#include "utils/Format.hpp"
#include "utils/ExceptionHandler.hpp"

#include "models/User.hpp"

#include "enums/Enums.hpp"

#include "services/UserService.hpp"

namespace controllers
{
    void LogController::printListUsers(std::vector<models::User> users, std::vector<enums::UserInfo> userInfo) {
        try {
            std::string borderLine = "+";
            std::string header = "|";
            for(const auto& info : userInfo) {
                int width = enums::getCellSize(info);
                header += " " + utils::format::formatCell(enums::to_string(info), width) + "|";
                borderLine += "-" + utils::format::formatBorder(width) + "+";
            }
            utils::MessageHandler::logMessage(borderLine);
            utils::MessageHandler::logMessage(header);
            utils::MessageHandler::logMessage(borderLine);

            for (const auto& user : users) {
                std::ostringstream oss;
                for(const auto& info : userInfo) {
                    int width = enums::getCellSize(info);
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
} // namespace controllers

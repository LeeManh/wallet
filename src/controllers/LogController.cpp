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
    void LogController::printListUsers(std::vector<models::User> users,
                                    std::vector<enums::UserInfo> userInfo) {
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

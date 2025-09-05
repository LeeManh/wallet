#include "controllers/WalletController.hpp"

#include "utils/ExceptionHandler.hpp"
#include "utils/Format.hpp"
#include "utils/MessageHandler.hpp"

namespace controllers {

/**
 * @brief Tạo ví mới cho người dùng.
 *
 * Input:
 *   - userId: ID của người dùng cần tạo ví.
 *   - initialBalance: Số dư khởi tạo cho ví.
 *
 * Output:
 *   - Trả về true nếu tạo ví thành công.
 *   - Trả về false nếu xảy ra lỗi (đồng thời gọi ExceptionHandler để xử lý).
 *
 * Thủ tục xử lý:
 *   1. Gọi WalletService::createWallet với userId và initialBalance.
 *   2. Nếu thành công → trả về true.
 *   3. Nếu có exception xảy ra:
 *        - Gọi ExceptionHandler để log lỗi.
 *        - Trả về false.
 */
  bool WalletController::createWallet(int userId, double initialBalance) {
  try {
    return services::WalletService::createWallet(userId, initialBalance);
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return false;
  }
}

/**
 * @brief Lấy ví của người dùng theo userId và hiển thị số dư.
 *
 * Input:
 *   - userId: ID của người dùng cần lấy ví.
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Nếu tìm thấy ví → in ra số dư điểm hiện tại.
 *   - Nếu không tìm thấy ví → in thông báo lỗi.
 *   - Nếu có lỗi hệ thống → ExceptionHandler sẽ xử lý và log ra màn hình.
 *
 * Thủ tục xử lý:
 *   1. Gọi WalletService::getWalletByUserId để lấy ví theo userId.
 *   2. Nếu không tìm thấy ví:
 *        - Hiển thị thông báo lỗi "Không tìm thấy ví của bạn".
 *   3. Nếu tìm thấy ví:
 *        - Lấy số điểm hiện tại.
 *        - Format số điểm thành chuỗi đẹp (formatPoint).
 *        - In ra thông báo số dư cho người dùng.
 *   4. Nếu có exception (lỗi bất kỳ):
 *        - Gọi ExceptionHandler để log lỗi chi tiết.
 */
void WalletController::getWalletByUserId(int userId) {
  try {
    // Gọi service để lấy ví theo userId
    auto wallet = services::WalletService::getWalletByUserId(userId);
    if (!wallet) {
      utils::MessageHandler::logError("Không tìm thấy ví của bạn");
    } else {
      utils::MessageHandler::logMessage(
          "Số dư điểm hiện tại của bạn: " +
          utils::format::formatPoint(wallet.value().getPoint()) + " điểm");
    }
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

/**
 * @brief Lấy ví hệ thống và hiển thị số dư hiện tại.
 *
 * Input:
 *   - Không có tham số đầu vào.
 *
 * Output:
 *   - Không trả về giá trị (void).
 *   - Nếu ví hệ thống tồn tại → in số dư ra log.
 *   - Nếu ví hệ thống không tồn tại hoặc có lỗi → in thông báo lỗi và gợi ý kiểm tra cấu hình.
 *   - Nếu có exception (lỗi runtime) → gọi ExceptionHandler để xử lý.
 *
 * Thủ tục xử lý:
 *   1. Gọi WalletService::getSystemWallet để lấy ví hệ thống.
 *   2. Nếu ví tồn tại:
 *        - Lấy số dư (point).
 *        - Format số điểm thành chuỗi dễ đọc (formatPoint).
 *        - In ra thông báo "Số dư ví hệ thống hiện tại".
 *   3. Nếu ví không tồn tại hoặc trả về rỗng:
 *        - In thông báo lỗi "Không tìm thấy ví hệ thống...".
 *        - In thêm gợi ý "Vui lòng kiểm tra lại cấu hình hệ thống".
 *   4. Nếu có exception (vd: lỗi database, lỗi logic):
 *        - ExceptionHandler sẽ xử lý và log lỗi ra màn hình.
 */
void WalletController::getSystemWallet() {
  try {
    // Gọi service để lấy ví hệ thống
    auto systemWallet = services::WalletService::getSystemWallet();

    if (systemWallet) {
      // Nếu có ví hệ thống → in số dư
      utils::MessageHandler::logMessage(
          "Số dư ví hệ thống hiện tại: " +
          utils::format::formatPoint(systemWallet.value().getPoint()) +
          " điểm");
    } else {
       // Nếu không có ví hệ thống → báo lỗi + gợi ý kiểm tra cấu hình
      utils::MessageHandler::logError(
          "Không tìm thấy ví hệ thống hoặc có lỗi xảy ra!");
      utils::MessageHandler::logMessage(
          "Vui lòng kiểm tra lại cấu hình hệ thống.");
    }
  } catch (const std::exception& e) {
    // Bắt và xử lý mọi exception phát sinh
    utils::ExceptionHandler::handleException(e);
  }
}

/**
 * @brief Lấy danh sách tất cả ví trong hệ thống.
 *
 * Input:
 *   - Không có tham số đầu vào.
 *
 * Output:
 *   - Trả về một vector<Wallet> chứa toàn bộ ví lấy từ hệ thống.
 *   - Nếu xảy ra lỗi, log lỗi qua ExceptionHandler và trả về vector rỗng.
 */
std::vector<models::Wallet> WalletController::getAllWallets() {
  try {
    return services::WalletService::getAllWallets();
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return std::vector<models::Wallet>();
  }
}

/**
 * @brief In danh sách tất cả ví trong hệ thống ra log.
 *
 * Input:
 *   - Không có tham số đầu vào.
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Kết quả được in ra log dưới dạng bảng hoặc danh sách.
 *   - Nếu xảy ra lỗi, sẽ được xử lý bởi ExceptionHandler.
 */
void WalletController::printListWallet() {
  try {
    services::WalletService::printListWallet();
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

/**
 * @brief Kiểm tra xem một ví có thuộc sở hữu của user hay không.
 *
 * Input:
 *   - userId: ID của người dùng cần kiểm tra.
 *   - walletId: ID của ví cần kiểm tra.
 *
 * Output:
 *   - Trả về true nếu ví thuộc sở hữu của user.
 *   - Trả về false nếu không tìm thấy ví, ví không thuộc user, hoặc có lỗi xảy ra.
 *
 * Thủ tục xử lý:
 *   1. Gọi WalletService::getWalletByUserId(userId) để lấy ví gắn với user (trường hợp hệ thống mỗi user chỉ có một ví).
 *        - Nếu tìm thấy ví, so sánh ID ví lấy được với walletId:
 *            - Nếu trùng: trả về true.
 *            - Nếu không trùng: tiếp tục bước 2.
 *   2. Nếu hệ thống có thể có nhiều ví cho một user:
 *        - Lấy toàn bộ danh sách ví từ WalletService::getAllWallets().
 *        - Duyệt qua từng ví:
 *            - Nếu có ví có userId khớp và ID ví bằng walletId → trả về true.
 *   3. Nếu không có ví nào khớp trong cả 2 bước trên → trả về false.
 *   4. Nếu trong quá trình xử lý xảy ra exception:
 *        - Gọi ExceptionHandler để xử lý.
 *        - Trả về false.
 */
bool WalletController::isWalletOwnedByUser(int userId, int walletId) {
  try {
    // Trường hợp hệ thống mỗi user chỉ có 1 ví:
    if (auto w = services::WalletService::getWalletByUserId(userId)) {
      // Ưu tiên dùng getter theo model của bạn; nếu model là getWalletId() thì đổi lại cho khớp
      return w->getId() == walletId; 
    }

    // Phòng khi hệ thống có nhiều ví / API khác: quét danh sách để chắc chắn
    for (const auto& w : services::WalletService::getAllWallets()) {
      // Nếu model là getUserId()/getId() khác tên, đổi lại cho đúng project của bạn
      if (w.getUserId() == userId && w.getId() == walletId) {
        return true;
      }
    }
    return false;
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return false;
  }
}

/**
 * @brief Lấy ID chủ sở hữu của một ví theo walletId.
 *
 * Input:
 *   - walletId: ID của ví cần tìm chủ sở hữu.
 *
 * Output:
 *   - Trả về std::optional<int>:
 *       + Giá trị userId nếu tìm thấy ví có ID khớp.
 *       + std::nullopt nếu không tìm thấy hoặc có lỗi xảy ra.
 */
std::optional<int> WalletController::getOwnerIdByWalletId(int walletId) {
  try {
    for (const auto& w : services::WalletService::getAllWallets()) {
      // Đổi getId/getUserId theo đúng getter của model bạn nếu khác tên
      if (w.getId() == walletId) {
        return w.getUserId();
      }
    }
    return std::nullopt;
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return std::nullopt;
  }
}

/**
 * @brief Lấy tên (hoặc mã định danh) chủ sở hữu của ví dựa trên walletId.
 *
 * Input:
 *   - walletId: ID của ví cần tìm chủ sở hữu.
 *
 * Output:
 *   - Trả về chuỗi định danh:
 *       + "user#<userId>" nếu tìm thấy chủ sở hữu.
 *       + "W#<walletId>" nếu không tìm thấy hoặc có lỗi xảy ra.
 */
std::string WalletController::getOwnerNameByWalletId(int walletId) {
  try {
    auto ownerId = getOwnerIdByWalletId(walletId);
    if (!ownerId) return "W#" + std::to_string(walletId);   // không tìm thấy ví
    // Chưa có UserService -> hiển thị theo userId
    return "user#" + std::to_string(*ownerId);
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
    return "W#" + std::to_string(walletId);
  }
}
}  // namespace controllers

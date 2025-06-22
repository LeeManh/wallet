#include "controllers/TransactionController.hpp"

#include <optional>

#include "exceptions/Exception.hpp"
#include "services/WalletService.hpp"
#include "utils/ExceptionHandler.hpp"
#include "utils/MessageHandler.hpp"

namespace controllers {

void TransactionController::transferPoints(int fromUserId, int toUserId,
                                           double points) {
  try {
    // Lấy ví của người nhận và người gửi
    auto fromWallet = services::WalletService::getWalletByUserId(fromUserId);
    auto toWallet = services::WalletService::getWalletByUserId(toUserId);

    // Kiểm tra ví tồn tại không
    if (!fromWallet.has_value())
      throw exceptions::NotFoundException("Không tìm thấy ví chuyển!");
    if (!toWallet.has_value())
      throw exceptions::NotFoundException("Không tìm thấy ví nhận!");

    // Kiểm tra số dư
    if (points < 0)
      throw exceptions::ValidationException("Số điểm chuyển không hợp lệ!");
    if (fromWallet.value().getPoint() < points)
      throw exceptions::ValidationException("Tài khoản không đủ điểm!");

    // Cập nhật só dư 2 ví
    services::WalletService::updatePoint(fromWallet.value().getId(), -points);
    services::WalletService::updatePoint(toWallet.value().getId(), +points);

    // Message thành công
    utils::MessageHandler::logSuccess("Chuyển điểm thành công!");
  } catch (const std::exception& e) {
    utils::ExceptionHandler::handleException(e);
  }
}

}  // namespace controllers
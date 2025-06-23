#include "controllers/TransactionController.hpp"

#include <optional>

#include "exceptions/Exception.hpp"
#include "services/OtpService.hpp"
#include "services/TransactionService.hpp"
#include "services/UserService.hpp"
#include "services/WalletService.hpp"
#include "utils/ExceptionHandler.hpp"
#include "utils/Input.hpp"
#include "utils/MessageHandler.hpp"

namespace controllers {

void TransactionController::transferPoints(int fromUserId, int toUserId,
                                           double points) {
  int transactionId = 0;  // Lưu transaction ID để update khi có lỗi

  try {
    // Không được gửi cho chính mình
    if (fromUserId == toUserId)
      throw exceptions::ValidationException("Không được gửi cho chính mình!");

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

    // Lấy email của user để gửi OTP
    auto userJson = services::UserService::findUserById(fromUserId);
    if (!userJson.has_value())
      throw exceptions::NotFoundException("Không tìm thấy user!");
    std::string email = userJson.value()["email"];

    // Tạo transaction trạng thái PENDING
    auto transaction = services::TransactionService::createTransaction(
        fromWallet.value().getId(), toWallet.value().getId(), points,
        enums::TransactionStatus::PENDING);
    transactionId = transaction.getId();  // Lưu ID để update khi có lỗi

    // Gửi OTP
    services::OtpService::generateAndSendOTP(fromUserId, email,
                                             enums::OTPType::TRANSFER_POINTS);

    // Input OTP
    std::string otpCode = utils::input::getInput("Nhập mã OTP đã được gửi: ");
    services::OtpService::verifyOTP(fromUserId, otpCode,
                                    enums::OTPType::TRANSFER_POINTS);

    // Thực hiện chuyển điểm
    services::WalletService::updatePoint(fromWallet.value().getId(), -points);
    services::WalletService::updatePoint(toWallet.value().getId(), +points);

    // Cập nhật transaction trạng thái thành công
    services::TransactionService::updateTransaction(
        transaction.getId(), enums::TransactionStatus::SUCCESS);

    // Message thành công
    utils::MessageHandler::logSuccess("Chuyển điểm thành công!");
  } catch (const std::exception& e) {
    // Cập nhật transaction trạng thái thất bại nếu đã tạo transaction
    if (transactionId > 0) {
      services::TransactionService::updateTransaction(
          transactionId, enums::TransactionStatus::FAILED);
    }

    utils::ExceptionHandler::handleException(e);
  }
}

}  // namespace controllers
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

/**
 * @brief Chuyển điểm từ một người dùng sang người dùng khác.
 *
 * Input:
 *   - fromUserId: ID người gửi điểm.
 *   - toUserId:   ID người nhận điểm.
 *   - points:     Số điểm cần chuyển.
 *
 * Output:
 *   - Không trả về giá trị.
 *   - Kết quả: 
 *       + Nếu thành công: cập nhật số dư 2 ví, transaction trạng thái SUCCESS,
 *         và in ra log thông báo thành công.
 *       + Nếu thất bại: transaction chuyển sang trạng thái FAILED,
 *         rollback số dư ví về trạng thái ban đầu (nếu cần),
 *         và in ra log thông báo lỗi.
 *
 * Thủ tục xử lý:
 *   1. Kiểm tra điều kiện hợp lệ:
 *        - Người gửi và người nhận không được trùng nhau.
 *        - Số điểm chuyển phải >= 0.
 *        - Ví người gửi và ví người nhận phải tồn tại.
 *        - Số dư ví người gửi phải đủ để chuyển.
 *
 *   2. Lấy thông tin user gửi để lấy email gửi OTP.
 *
 *   3. Tạo transaction với trạng thái PENDING,
 *      lưu transactionId để phục vụ rollback/cập nhật khi có lỗi.
 *
 *   4. Gửi OTP đến email người gửi,
 *      yêu cầu nhập mã OTP từ bàn phím và xác minh.
 *
 *   5. Nếu OTP hợp lệ:
 *        - Lưu snapshot số dư ví trước khi cập nhật.
 *        - Giảm điểm ví người gửi, tăng điểm ví người nhận.
 *        - Nếu cập nhật lỗi, ném ngoại lệ TransactionException.
 *
 *   6. Nếu cập nhật thành công:
 *        - Cập nhật transaction trạng thái SUCCESS.
 *        - In ra log thông báo thành công.
 *
 *   7. Nếu có ngoại lệ xảy ra:
 *        - Nếu transaction đã được tạo, cập nhật sang trạng thái FAILED.
 *        - Nếu lỗi thuộc loại TransactionException, rollback số dư ví
 *          về trạng thái snapshot trước đó.
 *        - In lỗi ra log thông qua ExceptionHandler.
 */
  void TransactionController::transferPoints(int fromUserId, int toUserId,
                                           double points) {
  int transactionId = 0;  // Placeholder transaction ID để update khi có lỗi
  models::Wallet* fromWalletSnapshot = nullptr;
  models::Wallet* toWalletSnapshot = nullptr;

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
    utils::MessageHandler::logMessage(
        "───────────────────────────────────────────────");
    services::OtpService::verifyOTP(fromUserId, otpCode,
                                    enums::OTPType::TRANSFER_POINTS);

    try {
      // Snapshot data của 2 ví trước khi thực hiện chuyển điểm
      fromWalletSnapshot = new models::Wallet(fromWallet.value());
      toWalletSnapshot = new models::Wallet(toWallet.value());

      // Thực hiện chuyển điểm
      services::WalletService::updatePoint(fromWallet.value().getId(), -points);
      services::WalletService::updatePoint(toWallet.value().getId(), +points);

      // Thử throw lỗi
      // throw exceptions::TransactionException("Lỗi khi chuyển điểm!");

    } catch (const std::exception& e) {
      throw exceptions::TransactionException(e.what());
    }

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

    // Rollback nếu có snapshot
    if (fromWalletSnapshot && toWalletSnapshot &&
        dynamic_cast<const exceptions::TransactionException*>(&e)) {
      services::WalletService::rollbackPoint(fromWalletSnapshot->getId(),
                                             fromWalletSnapshot->getPoint());
      services::WalletService::rollbackPoint(toWalletSnapshot->getId(),
                                             toWalletSnapshot->getPoint());
    }

    delete fromWalletSnapshot;
    delete toWalletSnapshot;

    utils::ExceptionHandler::handleException(e);
  }
}

}  // namespace controllers
#include "services/OtpService.hpp"

#include <cotp.h>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <nlohmann/json.hpp>

#include "enums/Enums.hpp"
#include "exceptions/Exception.hpp"
#include "models/Otp.hpp"
#include "utils/MessageHandler.hpp"
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace services {

/**
 * @brief Tạo và gửi mã OTP tới email người dùng.
 *
 * Mục đích:
 *   Sinh mã OTP, lưu vào hệ thống và gửi qua email cho người dùng để xác thực.
 *
 * Input:
 *   - userId: ID của người dùng.
 *   - email: Địa chỉ email nhận OTP.
 *   - otpType: Loại OTP (enum OTPType).
 *
 * Output:
 *   - true nếu OTP được tạo và gửi thành công.
 *   - false nếu xảy ra lỗi.
 */
bool OtpService::generateAndSendOTP(int userId, const std::string& email,
                                    enums::OTPType otpType) {
  try {
    // Tạo mã OTP
    std::string otpCode = generateOTPCode();

    // Tạo đối tượng OTP
    models::OTP otp(static_cast<int>(time(nullptr)),  // ID dựa trên timestamp
                    userId, otpCode, otpType);

    // Thiết lập thời gian hết hạn (5 phút)
    time_t expiryTime = time(nullptr) + 300;  // 5 minutes
    otp.setExpiresAt(expiryTime);

    // Lưu OTP
    if (!saveOTP(otp)) {
      utils::MessageHandler::logError("Không thể lưu OTP!");
      return false;
    }

    // Gửi OTP qua email
    if (!sendOTPEmail(email, otpCode)) {
      utils::MessageHandler::logError("Không thể gửi OTP qua email!");
      return false;
    }

    utils::MessageHandler::logSuccess("OTP đã được gửi đến email: " + email);
    return true;

  } catch (const std::exception& e) {
    utils::MessageHandler::logError("Lỗi khi tạo OTP: " +
                                    std::string(e.what()));
    return false;
  }
}

/**
 * @brief Xác thực mã OTP của người dùng.
 *
 * Mục đích:
 *   Kiểm tra mã OTP nhập vào có hợp lệ và chưa hết hạn hay không, sau đó xóa OTP đã dùng.
 *
 * Input:
 *   - userId: ID của người dùng.
 *   - otpCode: Mã OTP cần xác thực.
 *   - otpType: Loại OTP (enum OTPType).
 *
 * Output:
 *   - true nếu OTP hợp lệ.
 *   - Ném ValidationException nếu OTP sai hoặc hết hạn.
 */
bool OtpService::verifyOTP(int userId, const std::string& otpCode,
                           enums::OTPType otpType) {
  auto otps = loadOTPs();
  time_t currentTime = time(nullptr);

  for (size_t i = 0; i < otps.size(); ++i) {
    if (otps[i].getUserId() == userId && otps[i].getOtpCode() == otpCode &&
        otps[i].getOtpType() == otpType &&
        otps[i].getExpiresAt() > currentTime) {
      // OTP hợp lệ, xóa nó khỏi danh sách
      otps.erase(otps.begin() + i);

      // Lưu lại danh sách OTP đã cập nhật
      json otpArray = json::array();
      for (const auto& otpItem : otps) {
        json otpJson;
        otpJson["id"] = otpItem.getId();
        otpJson["userId"] = otpItem.getUserId();
        otpJson["otpCode"] = otpItem.getOtpCode();
        otpJson["otpType"] = static_cast<int>(otpItem.getOtpType());
        otpJson["expiresAt"] = otpItem.getExpiresAt();
        otpArray.push_back(otpJson);
      }

      utils::storage::writeJsonFile("data/otps.json", otpArray);

      utils::MessageHandler::logSuccess("OTP xác thực thành công!");
      return true;
    }
  }

  throw exceptions::ValidationException("OTP không hợp lệ hoặc đã hết hạn!");
}

/**
 * @brief Sinh mã OTP ngẫu nhiên.
 *
 * Mục đích:
 *   Tạo chuỗi OTP gồm 6 chữ số, có thời gian hiệu lực giới hạn.
 *
 * Input:
 *   - Không có.
 *
 * Output:
 *   - Chuỗi OTP 6 chữ số (std::string).
 */
std::string OtpService::generateOTPCode() {
  // Secret key được mã hóa Base32
  const char* secret = "JBSWY3DPEHPK3PXP";

  // Lấy thời gian hiện tại (UNIX timestamp) chia cho 30 để tạo timeStep
  // Điều này đảm bảo mỗi mã OTP chỉ hợp lệ trong 30 giây
  // uint64_t timeStep = time(nullptr) / 30;

  // Tạo mã TOTP gồm 6 chữ số, sử dụng thuật toán SHA1
  // get_totp có thể cấp phát bộ nhớ động, nên phải free sau khi dùng
  cotp_error_t err;
  char* rawOtp = get_totp(secret, 6, 30, SHA1, &err);

  // Chuyển từ C-string (char*) sang std::string để tiện sử dụng
  std::string otpCode = rawOtp;

  // Giải phóng bộ nhớ đã cấp phát từ get_totp
  free(rawOtp);

  // Trả về mã OTP đã tạo
  return otpCode;
}

/**
 * @brief Lưu thông tin OTP vào file lưu trữ.
 *
 * Mục đích:
 *   Ghi thông tin OTP mới vào file JSON để lưu trữ và kiểm tra sau này.
 *
 * Input:
 *   - otp: Đối tượng OTP cần lưu.
 *
 * Output:
 *   - true nếu lưu thành công.
 *   - false nếu xảy ra lỗi khi lưu.
 */
bool OtpService::saveOTP(const models::OTP& otp) {
  try {
    // Đọc danh sách OTP hiện tại từ file JSON (nếu file chưa tồn tại sẽ trả về
    // mảng rỗng)
    json otps = utils::storage::readJsonFile("data/otps.json");

    // Chuyển đối tượng OTP từ C++ sang định dạng JSON
    json otpJson;
    otpJson["id"] = otp.getId();            // ID duy nhất của OTP
    otpJson["userId"] = otp.getUserId();    // ID của người dùng
    otpJson["otpCode"] = otp.getOtpCode();  // Mã OTP
    otpJson["otpType"] =
        static_cast<int>(otp.getOtpType());  // Kiểu OTP (enum chuyển sang int)
    otpJson["expiresAt"] = otp.getExpiresAt();  // Thời điểm hết hạn

    // Thêm bản ghi OTP mới vào danh sách
    otps.push_back(otpJson);

    // Ghi danh sách OTP đã cập nhật trở lại vào file
    if (!utils::storage::writeJsonFile("data/otps.json", otps)) {
      utils::MessageHandler::logError("Lỗi khi lưu OTP");
      return false;
    }

    return true;
  } catch (const std::exception& e) {
    // In lỗi ra console nếu có ngoại lệ xảy ra khi đọc/ghi file
    utils::MessageHandler::logError("Lỗi khi lưu OTP");
    return false;
  }
}

/**
 * @brief Tải toàn bộ OTP từ file lưu trữ.
 *
 * Mục đích:
 *   Đọc dữ liệu OTP từ file JSON và chuyển thành danh sách đối tượng OTP.
 *
 * Input:
 *   - Không có.
 *
 * Output:
 *   - Vector chứa các đối tượng OTP.
 */
std::vector<models::OTP> OtpService::loadOTPs() {
  std::vector<models::OTP> otps;

  try {
    json otpData = utils::storage::readJsonFile("data/otps.json");

    for (const auto& item : otpData) {
      models::OTP otp(item["id"], item["userId"], item["otpCode"],
                      static_cast<enums::OTPType>(item["otpType"]));
      otp.setExpiresAt(item["expiresAt"]);
      otps.push_back(otp);
    }

  } catch (const std::exception& e) {
    // Return empty vector if file doesn't exist or error occurs
  }

  return otps;
}


/**
 * @brief Gửi mã OTP qua email (mô phỏng).
 *
 * Mục đích:
 *   Hiển thị thông tin OTP gửi qua email, phục vụ mục đích demo hoặc log.
 *
 * Input:
 *   - email: Địa chỉ email nhận OTP.
 *   - otpCode: Mã OTP.
 *
 * Output:
 *   - true (luôn trả về thành công trong bản mô phỏng).
 */
bool OtpService::sendOTPEmail(const std::string& email,
                              const std::string& otpCode) {
  utils::MessageHandler::logMessage(
      "┌─────────────────────────────────────────────┐");
  utils::MessageHandler::logMessage(
      "│              GỬI OTP QUA EMAIL              │");
  utils::MessageHandler::logMessage(
      "└─────────────────────────────────────────────┘");

  utils::MessageHandler::logMessage("- Đến: " + email);
  utils::MessageHandler::logMessage("- Mã OTP: " + otpCode);
  utils::MessageHandler::logMessage("- Thời gian hiệu lực: 5 phút");
  utils::MessageHandler::logMessage(
      "───────────────────────────────────────────────");

  return true;
}

}  // namespace services
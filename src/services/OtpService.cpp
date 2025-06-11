#include "services/OtpService.hpp"

#include <cotp.h>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <nlohmann/json.hpp>

#include "models/Otp.hpp"
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace services {

bool OtpService::generateAndSendOTP(int userId, const std::string& email) {
  try {
    // Tạo mã OTP
    std::string otpCode = generateOTPCode();

    // Tạo đối tượng OTP
    models::OTP otp(static_cast<int>(time(nullptr)),  // ID dựa trên timestamp
                    userId, otpCode, models::OTPType::INFO_CHANGE);

    // Thiết lập thời gian hết hạn (5 phút)
    time_t expiryTime = time(nullptr) + 300;  // 5 minutes
    otp.setExpiresAt(expiryTime);

    // Lưu OTP
    if (!saveOTP(otp)) {
      std::cout << "Không thể lưu OTP!" << std::endl;
      return false;
    }

    // Gửi OTP qua email
    if (!sendOTPEmail(email, otpCode)) {
      std::cout << "Không thể gửi OTP qua email!" << std::endl;
      return false;
    }

    std::cout << "OTP đã được gửi đến email: " << email << std::endl;
    return true;

  } catch (const std::exception& e) {
    std::cout << "Lỗi khi tạo OTP: " << e.what() << std::endl;
    return false;
  }
}

// Xác thực OTP
bool OtpService::verifyOTP(int userId, const std::string& otpCode,
                           models::OTPType otpType) {
  try {
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
          otpJson["createdAt"] = otpItem.getCreatedAt();
          otpJson["expiresAt"] = otpItem.getExpiresAt();
          otpArray.push_back(otpJson);
        }

        utils::storage::writeJsonFile("data/otps.json", otpArray);

        std::cout << "OTP xác thực thành công!" << std::endl;
        return true;
      }
    }

    std::cout << "OTP không hợp lệ hoặc đã hết hạn!" << std::endl;
    return false;

  } catch (const std::exception& e) {
    std::cout << "Lỗi khi xác thực OTP: " << e.what() << std::endl;
    return false;
  }
}

std::string OtpService::generateOTPCode() {
  // Secret key được mã hóa Base32
  const char* secret = "JBSWY3DPEHPK3PXP";

  // Lấy thời gian hiện tại (UNIX timestamp) chia cho 30 để tạo timeStep
  // Điều này đảm bảo mỗi mã OTP chỉ hợp lệ trong 30 giây
  uint64_t timeStep = time(nullptr) / 30;

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
    otpJson["createdAt"] = otp.getCreatedAt();  // Thời điểm tạo OTP
    otpJson["expiresAt"] = otp.getExpiresAt();  // Thời điểm hết hạn

    // Thêm bản ghi OTP mới vào danh sách
    otps.push_back(otpJson);

    // Ghi danh sách OTP đã cập nhật trở lại vào file
    return utils::storage::writeJsonFile("data/otps.json", otps);
  } catch (const std::exception& e) {
    // In lỗi ra console nếu có ngoại lệ xảy ra khi đọc/ghi file
    std::cout << "Lỗi khi lưu OTP: " << e.what() << std::endl;
    return false;
  }
}

std::vector<models::OTP> OtpService::loadOTPs() {
  std::vector<models::OTP> otps;

  try {
    json otpData = utils::storage::readJsonFile("data/otps.json");

    for (const auto& item : otpData) {
      models::OTP otp(item["id"], item["userId"], item["otpCode"],
                      static_cast<models::OTPType>(item["otpType"]));
      otp.setExpiresAt(item["expiresAt"]);
      otps.push_back(otp);
    }

  } catch (const std::exception& e) {
    // Return empty vector if file doesn't exist or error occurs
  }

  return otps;
}

bool OtpService::sendOTPEmail(const std::string& email,
                              const std::string& otpCode) {
  std::cout << "=====================================" << std::endl;
  std::cout << "        GỬI OTP QUA EMAIL" << std::endl;
  std::cout << "=====================================" << std::endl;
  std::cout << "Đến: " << email << std::endl;
  std::cout << "Mã OTP: " << otpCode << std::endl;
  std::cout << "Thời gian hiệu lực: 5 phút" << std::endl;
  std::cout << "=====================================" << std::endl;

  return true;
}

}  // namespace services
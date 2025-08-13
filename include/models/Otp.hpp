#pragma once

#include <string>

#include "enums/Enums.hpp"

namespace models {

/**
 * @class OTP
 * @brief Đại diện cho mã OTP (One-Time Password) dùng để xác thực người dùng.
 *
 * Lớp này lưu trữ thông tin về mã OTP, loại OTP, thời gian hết hạn
 * và các thông tin liên quan đến người dùng đã yêu cầu OTP.
 */
  class OTP {
 private:
  
  int id;                 // ID duy nhất của mã OTP.            
  int userId;             // ID của người dùng sở hữu OTP này.
  std::string otpCode;    // Mã OTP
  enums::OTPType otpType; // Loại OTP (ví dụ: đăng nhập, quên mật khẩu, v.v.).
  time_t expiresAt;       // Thời gian hết hạn của mã OTP (theo timestamp).

 public:

  /**
   * @brief Constructor khởi tạo đối tượng OTP.
   * @param id ID của OTP.
   * @param userId ID của người dùng.
   * @param otpCode Chuỗi mã OTP.
   * @param otpType Loại OTP.
   */
  OTP(const int id, const int userId, const std::string& otpCode,
      const enums::OTPType& otpType);

  /** 
   * @brief Lấy ID của OTP.
   * @return ID của OTP.
   */
  int getId() const;

  /**
   * @brief Lấy ID của người dùng sở hữu OTP.
   * @return ID người dùng.
   */
  int getUserId() const;

  /**
   * @brief Lấy chuỗi mã OTP.
   * @return Chuỗi OTP.
   */
  std::string getOtpCode() const;

  /**
   * @brief Lấy loại OTP.
   * @return Loại OTP (enum OTPType).
   */
  enums::OTPType getOtpType() const;

  /**
   * @brief Lấy thời gian hết hạn của OTP.
   * @return Thời gian hết hạn (timestamp).
   */
  time_t getExpiresAt() const;

  /**
   * @brief Cập nhật mã OTP mới.
   * @param newOtpCode Mã OTP mới.
   */
  void setOtpCode(const std::string& newOtpCode);

  /**
   * @brief Cập nhật thời gian hết hạn mới.
   * @param newExpiresAt Thời gian hết hạn mới.
   */
  void setExpiresAt(const time_t& newExpiresAt);
};

}  // namespace models

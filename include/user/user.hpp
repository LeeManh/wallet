#ifndef USER_HPP
#define USER_HPP

#include <string>

namespace user {

class User {
 private:
  std::string username;      // Tên đăng nhập (unique)
  std::string passwordHash;  // Mật khẩu đã được hash
  std::string fullName;      // Họ và tên đầy đủ
  bool isAdmin;              // Phân quyền admin

 public:
  // Constructor
  User(const std::string& username, const std::string& passwordHash,
       const std::string& fullName, bool isAdmin = false);

  // Getters
  std::string getUsername() const;
  std::string getFullName() const;
  bool isAdminUser() const;
  std::string getPasswordHash() const;

  // Setters
  void setPassword(const std::string& newPassword);
  void setFullName(const std::string& newFullName);
};

}  // namespace user
#endif

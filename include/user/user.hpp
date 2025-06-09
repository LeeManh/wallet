#ifndef USER_HPP
#define USER_HPP

#include <string>

#include "bcrypt/BCrypt.hpp"

using namespace std;

namespace user {

class User {
 private:
  string username;      // Tên đăng nhập (unique)
  string passwordHash;  // Mật khẩu đã được hash
  string fullName;      // Họ và tên đầy đủ
  bool isAdmin;         // Phân quyền admin

 public:
  // Constructor
  User(const string& username, const string& password, const string& fullName,
       bool isAdmin = false);

  // Getters
  string getUsername() const;
  string getFullName() const;
  bool isAdminUser() const;
  string getPasswordHash() const;

  // Setters
  void setPassword(const string& newPassword);
  void setFullName(const string& newFullName);

  // Authentication methods
  bool verifyPassword(const string& password) const;
};

}  // namespace user

#endif
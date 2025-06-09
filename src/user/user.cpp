#include "user/user.hpp"

#include <string>

namespace user {

// Parameterized constructor
User::User(const string& username, const string& password,
           const string& fullName, bool isAdmin)
    : username(username), fullName(fullName), isAdmin(isAdmin) {
  // Hash password using bcrypt
  passwordHash = BCrypt::generateHash(password);
}

// Getters
string User::getUsername() const { return username; }

string User::getFullName() const { return fullName; }

bool User::isAdminUser() const { return isAdmin; }

string User::getPasswordHash() const { return passwordHash; }

// Setters
void User::setPassword(const string& newPassword) {
  // Hash new password using bcrypt
  passwordHash = BCrypt::generateHash(newPassword);
}

void User::setFullName(const string& newFullName) { fullName = newFullName; }

// Authentication
bool User::verifyPassword(const string& password) const {
  // Verify password using bcrypt
  return BCrypt::validatePassword(password, passwordHash);
}

}  // namespace user
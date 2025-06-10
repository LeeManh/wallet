#include "models/User.hpp"

#include <string>

#include "utils/hash.hpp"

namespace models {

// Parameterized constructor
User::User(const std::string& username, const std::string& passwordHash,
           const std::string& fullName, bool isAdmin)
    : username(username),
      passwordHash(passwordHash),
      fullName(fullName),
      isAdmin(isAdmin) {}

// Getters
std::string User::getUsername() const { return username; }
std::string User::getFullName() const { return fullName; }
bool User::isAdminUser() const { return isAdmin; }
std::string User::getPasswordHash() const { return passwordHash; }

// Setters
void User::setPassword(const std::string& newPassword) {
  passwordHash = utils::hash::generatePasswordHash(newPassword);
}
void User::setFullName(const std::string& newFullName) {
  fullName = newFullName;
}

}  // namespace models
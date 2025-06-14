#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include "models/User.hpp"
#include "utils/Hash.hpp"
#include "utils/MessageHandler.hpp"
#include "utils/Storage.hpp"

using json = nlohmann::json;

namespace services {

class UserService {
 public:
  // User data validation
  bool validateUserData(const std::string& username, const std::string& email);

  // User creation
  models::User createUser(const std::string& username,
                          const std::string& password, const std::string& email,
                          const std::string& fullName);

  // User persistence
  bool saveUser(const models::User& user);

  // User queries
  bool findUserById(const int userId, json& userData);
  bool findUserByUsername(const std::string& username, json& userData);
  std::string getUserEmail(int userId);

 private:
  bool isUsernameExists(const json& users, const std::string& username);
  bool isEmailExists(const json& users, const std::string& email);
};

}  // namespace services
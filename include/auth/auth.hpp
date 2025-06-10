#ifndef AUTH_HPP
#define AUTH_HPP

#include <exception>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "user/user.hpp"

using json = nlohmann::json;

namespace auth {

std::pair<bool, bool> login(const std::string& username,
                            const std::string& password);
bool registerUser(const std::string& username, const std::string& password,
                  const std::string& fullName);
bool isUserExists(const json& users, const std::string& username);

}  // namespace auth

#endif
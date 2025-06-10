#ifndef AUTH_HPP
#define AUTH_HPP

#include <exception>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "user/user.hpp"

using json = nlohmann::json;

namespace auth {

bool login(const std::string& username, const std::string& password);
bool registerUser(const std::string& username, const std::string& password,
                  const std::string& fullName);

}  // namespace auth

#endif
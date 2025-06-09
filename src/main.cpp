#include <iostream>

#include "user/user.hpp"

using namespace std;

int main() {
  // Test tạo user thông thường
  user::User user1("john", "password123", "John Doe");
  cout << "=== Test User 1 ===" << endl;
  cout << "Username: " << user1.getUsername() << endl;
  cout << "Full name: " << user1.getFullName() << endl;
  cout << "Is admin: " << (user1.isAdminUser() ? "Yes" : "No") << endl;
  cout << "Password hash: " << user1.getPasswordHash() << endl;
  cout << "Password verification: "
       << (user1.verifyPassword("password123") ? "Correct" : "Incorrect")
       << endl;
  cout << endl;

  // Test tạo user admin
  user::User admin("admin", "admin123", "Admin User", true);
  cout << "=== Test Admin User ===" << endl;
  cout << "Username: " << admin.getUsername() << endl;
  cout << "Full name: " << admin.getFullName() << endl;
  cout << "Is admin: " << (admin.isAdminUser() ? "Yes" : "No") << endl;
  cout << "Password hash: " << admin.getPasswordHash() << endl;
  cout << "Password verification: "
       << (admin.verifyPassword("admin123") ? "Correct" : "Incorrect") << endl;
  cout << endl;

  // Test thay đổi thông tin
  cout << "=== Test Change Information ===" << endl;
  user1.setFullName("John Doe Updated");
  user1.setPassword("newpassword123");
  cout << "New full name: " << user1.getFullName() << endl;
  cout << "New password hash: " << user1.getPasswordHash() << endl;
  cout << "New password verification: "
       << (user1.verifyPassword("newpassword123") ? "Correct" : "Incorrect")
       << endl;

  return 0;
}
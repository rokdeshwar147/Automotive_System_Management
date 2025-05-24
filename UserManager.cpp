#include "UserManager.h"
#include <iostream>
#include <sstream>
#include <sqlite3.h>

UserManager::UserManager(DatabaseManager& db) : dbManager(db) {}

void UserManager::registerUser() {
    std::string username, password, role;

    std::cout << "Enter username: \n";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    std::cout << "Enter role (admin/user): ";
    std::getline(std::cin, role);

    std::stringstream query;
    query << "INSERT INTO Users (Username, Password, Role) VALUES ("
          << "'" << username << "', '" << password << "', '" << role << "');";

    if (dbManager.executeQuery(query.str())) {
        std::cout << "User registered successfully.\n";
    }
}

bool UserManager::loginUser() {
    std::string username, password;

    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    std::string query = "SELECT Role FROM Users WHERE Username='" + username +
                        "' AND Password='" + password + "';";

    sqlite3* db = dbManager.getDB();
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::cout << "Login successful. Role: " << role << "\n";
            sqlite3_finalize(stmt);
            return true;
        }
        sqlite3_finalize(stmt);
    }

    std::cout << "Invalid credentials.\n";
    return false;
}

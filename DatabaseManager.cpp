#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& databaseName)
    : db(nullptr), dbName(databaseName) {}

DatabaseManager::~DatabaseManager() {
    close();
}

bool DatabaseManager::open() {
    if (sqlite3_open(dbName.c_str(), &db) == SQLITE_OK) {
        return true;
    } else {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
}

void DatabaseManager::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::executeQuery(const std::string& query) {
    char* errorMsg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
        return false;
    }
    return true;
}

sqlite3* DatabaseManager::getDB() {
    return db;
}

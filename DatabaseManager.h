#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <sqlite3.h>
#include <string>

class DatabaseManager {
private:
    sqlite3* db;
    std::string dbName;

public:
    DatabaseManager(const std::string& databaseName);
    ~DatabaseManager();

    bool open();
    void close();
    bool executeQuery(const std::string& query);
    sqlite3* getDB();
};

#endif

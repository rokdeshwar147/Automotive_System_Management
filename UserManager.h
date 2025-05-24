#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "DatabaseManager.h"
#include <string>

class UserManager {
private:
    DatabaseManager& dbManager;

public:
    UserManager(DatabaseManager& db);
    void registerUser();
    bool loginUser();
};

#endif 

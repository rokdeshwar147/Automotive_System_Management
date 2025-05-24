#ifndef DTC_MANAGER_H
#define DTC_MANAGER_H

#include "DatabaseManager.h"
#include <string>

class DTCManager {
private:
    DatabaseManager& dbManager;

public:
    DTCManager(DatabaseManager& db);
    void addDTC();
    void viewDTCs();
    void updateDTC();
    void deleteDTC();
};

#endif 

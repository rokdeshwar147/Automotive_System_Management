#ifndef REAL_TIME_MONITOR_H
#define REAL_TIME_MONITOR_H

#include "DatabaseManager.h"

class RealTimeMonitor {
private:
    DatabaseManager& dbManager;

public:
    RealTimeMonitor(DatabaseManager& db);
    void simulateAndLogData();
};

#endif 

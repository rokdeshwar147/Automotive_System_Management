#ifndef ANALYTICS_MANAGER_H
#define ANALYTICS_MANAGER_H

#include "DatabaseManager.h"

class AnalyticsManager {
private:
    DatabaseManager& dbManager;

public:
    AnalyticsManager(DatabaseManager& db);
    void showVehiclePerformanceMetrics();
    void showFrequentDTCs();
};

#endif 

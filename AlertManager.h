#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include "DatabaseManager.h"

class AlertManager {
private:
    DatabaseManager& dbManager;

public:
    AlertManager(DatabaseManager& db);
    void checkForRealTimeAlerts();
    void checkForDTCAlerts();
};

#endif

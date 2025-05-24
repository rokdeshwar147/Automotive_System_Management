#ifndef VEHICLE_MANAGER_H
#define VEHICLE_MANAGER_H

#include "DatabaseManager.h"
#include <string>

class VehicleManager {
private:
    DatabaseManager& dbManager;

public:
    VehicleManager(DatabaseManager& db);
    void addVehicle();
    void viewVehicles();
    void updateVehicle();
    void deleteVehicle();
};

#endif

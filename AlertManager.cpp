#include "AlertManager.h"
#include <iostream>
#include <sstream>
#include <ctime>

AlertManager::AlertManager(DatabaseManager& db) : dbManager(db) {}

void AlertManager::checkForRealTimeAlerts() {
    std::string query = R"(
        SELECT ID, VehicleID, EngineSpeed, CoolantTemperature, FuelLevel
        FROM RealTimeData
        ORDER BY ID DESC LIMIT 1;
    )";

    sqlite3* db = dbManager.getDB();
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            int vehicleID = sqlite3_column_int(stmt, 1);
            int engineSpeed = sqlite3_column_int(stmt, 2);
            float coolantTemp = static_cast<float>(sqlite3_column_double(stmt, 3));
            float fuelLevel = static_cast<float>(sqlite3_column_double(stmt, 4));

            std::stringstream alertQuery;
            time_t now = time(0);
            std::string timestamp = ctime(&now);
            timestamp.pop_back(); // remove newline

            bool triggered = false;

            if (engineSpeed > 5000) {
                alertQuery << "INSERT INTO Alerts (VehicleID, Timestamp, AlertType, Description) VALUES ("
                           << vehicleID << ", '" << timestamp << "', 'Engine RPM', 'Engine speed exceeded safe limit');";
                dbManager.executeQuery(alertQuery.str());
                triggered = true;
                alertQuery.str(""); // reset
            }

            if (coolantTemp > 110) {
                alertQuery << "INSERT INTO Alerts (VehicleID, Timestamp, AlertType, Description) VALUES ("
                           << vehicleID << ", '" << timestamp << "', 'Coolant Temperature', 'Coolant temp too high');";
                dbManager.executeQuery(alertQuery.str());
                triggered = true;
                alertQuery.str("");
            }

            if (fuelLevel < 10) {
                alertQuery << "INSERT INTO Alerts (VehicleID, Timestamp, AlertType, Description) VALUES ("
                           << vehicleID << ", '" << timestamp << "', 'Fuel Level', 'Fuel critically low');";
                dbManager.executeQuery(alertQuery.str());
                triggered = true;
            }

            if (triggered) {
                std::cout << "One or more real-time alerts triggered.\n";
            } else {
                std::cout << "No real-time alerts.\n";
            }
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to evaluate real-time data.\n";
    }
}

void AlertManager::checkForDTCAlerts() {
    std::string query = "SELECT VehicleID, DTCCode, Description FROM DTCs;";
    sqlite3* db = dbManager.getDB();
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        time_t now = time(0);
        std::string timestamp = ctime(&now);
        timestamp.pop_back(); // remove newline

        bool alertCreated = false;

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int vehicleID = sqlite3_column_int(stmt, 0);
            std::string code = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

            std::stringstream alertQuery;
            alertQuery << "INSERT INTO Alerts (VehicleID, Timestamp, AlertType, Description) VALUES ("
                       << vehicleID << ", '" << timestamp << "', 'DTC Detected', 'DTC Code: "
                       << code << " - " << description << "');";

            dbManager.executeQuery(alertQuery.str());
            alertCreated = true;
        }

        if (alertCreated) {
            std::cout << "DTC alerts generated based on current DTCs.\n";
        } else {
            std::cout << "No DTCs found.\n";
        }

        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to check DTCs.\n";
    }
}

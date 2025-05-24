#include "AnalyticsManager.h"
#include <iostream>
#include <sqlite3.h>

AnalyticsManager::AnalyticsManager(DatabaseManager& db) : dbManager(db) {}

void AnalyticsManager::showVehiclePerformanceMetrics() {
    const char* query = R"(
        SELECT
            VehicleID,
            AVG(VehicleSpeed),
            AVG(FuelLevel)
        FROM RealTimeData
        GROUP BY VehicleID;
    )";

    sqlite3* db = dbManager.getDB();
    sqlite3_stmt* stmt;

    std::cout << "\n-- Vehicle Performance Metrics --\n";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int vehicleID = sqlite3_column_int(stmt, 0);
            double avgSpeed = sqlite3_column_double(stmt, 1);
            double avgFuel = sqlite3_column_double(stmt, 2);

            std::cout << "Vehicle ID: " << vehicleID
                      << ", Avg Speed: " << avgSpeed << " km/h"
                      << ", Avg Fuel Level: " << avgFuel << " %\n";
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to fetch vehicle performance metrics.\n";
    }
}

void AnalyticsManager::showFrequentDTCs() {
    const char* query = R"(
        SELECT DTCCode, COUNT(*) AS Frequency
        FROM DTCs
        GROUP BY DTCCode
        ORDER BY Frequency DESC
        LIMIT 5;
    )";

    sqlite3* db = dbManager.getDB();
    sqlite3_stmt* stmt;

    std::cout << "\n-- Most Frequent DTCs --\n";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string code = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            int freq = sqlite3_column_int(stmt, 1);

            std::cout << "DTC Code: " << code << ", Count: " << freq << '\n';
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to fetch DTC frequency data.\n";
    }
}

#include "ReportGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sqlite3.h>

ReportGenerator::ReportGenerator(DatabaseManager& db) : dbManager(db) {}

void ReportGenerator::generateConsoleReport() {
    std::stringstream buffer;
    exportReportToFile(""); // reuse logic without writing to file
}

void ReportGenerator::exportReportToFile(const std::string& filename) {
    std::stringstream report;

    sqlite3* db = dbManager.getDB();
    sqlite3_stmt* stmt;

    report << "\n--- Vehicle Summary ---\n";
    std::string query = "SELECT * FROM Vehicles;";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            report << "ID: " << sqlite3_column_int(stmt, 0)
                   << ", Make: " << sqlite3_column_text(stmt, 1)
                   << ", Model: " << sqlite3_column_text(stmt, 2)
                   << ", Year: " << sqlite3_column_int(stmt, 3)
                   << ", VIN: " << sqlite3_column_text(stmt, 4)
                   << ", Fuel: " << sqlite3_column_text(stmt, 5) << "\n";
        }
        sqlite3_finalize(stmt);
    }

    report << "\n--- DTC Summary ---\n";
    query = "SELECT VehicleID, DTCCode, Description, Severity FROM DTCs;";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            report << "Vehicle ID: " << sqlite3_column_int(stmt, 0)
                   << ", Code: " << sqlite3_column_text(stmt, 1)
                   << ", Desc: " << sqlite3_column_text(stmt, 2)
                   << ", Severity: " << sqlite3_column_text(stmt, 3) << "\n";
        }
        sqlite3_finalize(stmt);
    }

    report << "\n--- Alerts Summary ---\n";
    query = "SELECT VehicleID, Timestamp, AlertType, Description FROM Alerts ORDER BY Timestamp DESC LIMIT 10;";
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            report << "Vehicle ID: " << sqlite3_column_int(stmt, 0)
                   << ", Time: " << sqlite3_column_text(stmt, 1)
                   << ", Type: " << sqlite3_column_text(stmt, 2)
                   << ", Desc: " << sqlite3_column_text(stmt, 3) << "\n";
        }
        sqlite3_finalize(stmt);
    }

    // Output
    if (filename.empty()) {
        std::cout << report.str();
    } else {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << report.str();
            file.close();
            std::cout << "Report saved to " << filename << "\n";
        } else {
            std::cerr << "Failed to write to file.\n";
        }
    }
}

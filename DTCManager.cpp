#include "DTCManager.h"
#include <iostream>
#include <sstream>

DTCManager::DTCManager(DatabaseManager& db) : dbManager(db) {}

void DTCManager::addDTC() {
    int vehicleID;
    std::string dtcCode, description, severity;

    std::cout << "Enter Vehicle ID: ";
    std::cin >> vehicleID; std::cin.ignore();
    std::cout << "Enter DTC Code: ";
    std::getline(std::cin, dtcCode);
    std::cout << "Enter Description: ";
    std::getline(std::cin, description);
    std::cout << "Enter Severity: ";
    std::getline(std::cin, severity);

    std::stringstream query;
    query << "INSERT INTO DTCs (VehicleID, DTCCode, Description, Severity) VALUES ("
          << vehicleID << ", "
          << "'" << dtcCode << "', "
          << "'" << description << "', "
          << "'" << severity << "');";

    if (dbManager.executeQuery(query.str())) {
        std::cout << "DTC added successfully.\n";
    }
}

void DTCManager::viewDTCs() {
    std::string query = "SELECT * FROM DTCs;";
    sqlite3* db = dbManager.getDB();
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\n-- DTC Records --\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            int vehicleID = sqlite3_column_int(stmt, 1);
            std::string dtcCode = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string severity = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

            std::cout << "ID: " << id
                      << ", VehicleID: " << vehicleID
                      << ", DTC Code: " << dtcCode
                      << ", Description: " << description
                      << ", Severity: " << severity << '\n';
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to fetch DTCs.\n";
    }
}

void DTCManager::updateDTC() {
    int id;
    std::string dtcCode, description, severity;

    std::cout << "Enter DTC ID to update: ";
    std::cin >> id; std::cin.ignore();
    std::cout << "Enter new DTC Code: ";
    std::getline(std::cin, dtcCode);
    std::cout << "Enter new Description: ";
    std::getline(std::cin, description);
    std::cout << "Enter new Severity: ";
    std::getline(std::cin, severity);

    std::stringstream query;
    query << "UPDATE DTCs SET "
          << "DTCCode='" << dtcCode << "', "
          << "Description='" << description << "', "
          << "Severity='" << severity << "' "
          << "WHERE ID=" << id << ";";

    if (dbManager.executeQuery(query.str())) {
        std::cout << "DTC updated successfully.\n";
    }
}

void DTCManager::deleteDTC() {
    int id;
    std::cout << "Enter DTC ID to delete: ";
    std::cin >> id; std::cin.ignore();

    std::stringstream query;
    query << "DELETE FROM DTCs WHERE ID=" << id << ";";

    if (dbManager.executeQuery(query.str())) {
        std::cout << "DTC deleted successfully.\n";
    }
}

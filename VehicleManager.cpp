#include "VehicleManager.h"
#include <iostream>
#include <sstream>

VehicleManager::VehicleManager(DatabaseManager& db) : dbManager(db) {}

void VehicleManager::addVehicle() {
    std::string make, model, vin, fuelType;
    int year;

    std::cout << "Enter Make: "; std::getline(std::cin, make);
    std::cout << "Enter Model: "; std::getline(std::cin, model);
    std::cout << "Enter Year: "; std::cin >> year; std::cin.ignore();
    std::cout << "Enter VIN: "; std::getline(std::cin, vin);
    std::cout << "Enter Fuel Type: "; std::getline(std::cin, fuelType);

    std::stringstream query;
    query << "INSERT INTO Vehicles (Make, Model, Year, VIN, FuelType) VALUES ("
          << "'" << make << "', "
          << "'" << model << "', "
          << year << ", "
          << "'" << vin << "', "
          << "'" << fuelType << "');";

    if (dbManager.executeQuery(query.str())) {
        std::cout << "Vehicle added successfully.\n";
    }
}

void VehicleManager::viewVehicles() {
    std::string query = "SELECT * FROM Vehicles;";
    sqlite3* db = dbManager.getDB();
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        std::cout << "\n-- Vehicles --\n";
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string make = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int year = sqlite3_column_int(stmt, 3);
            std::string vin = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            std::string fuel = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

            std::cout << "ID: " << id
                      << ", Make: " << make
                      << ", Model: " << model
                      << ", Year: " << year
                      << ", VIN: " << vin
                      << ", Fuel: " << fuel << '\n';
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to fetch vehicles.\n";
    }
}

void VehicleManager::updateVehicle() {
    int id;
    std::string make, model, vin, fuelType;
    int year;

    std::cout << "Enter ID of vehicle to update: ";
    std::cin >> id; std::cin.ignore();
    std::cout << "Enter new Make: "; std::getline(std::cin, make);
    std::cout << "Enter new Model: "; std::getline(std::cin, model);
    std::cout << "Enter new Year: "; std::cin >> year; std::cin.ignore();
    std::cout << "Enter new VIN: "; std::getline(std::cin, vin);
    std::cout << "Enter new Fuel Type: "; std::getline(std::cin, fuelType);

    std::stringstream query;
    query << "UPDATE Vehicles SET "
          << "Make='" << make << "', "
          << "Model='" << model << "', "
          << "Year=" << year << ", "
          << "VIN='" << vin << "', "
          << "FuelType='" << fuelType << "' "
          << "WHERE ID=" << id << ";";

    if (dbManager.executeQuery(query.str())) {
        std::cout << "Vehicle updated successfully.\n";
    }
}

void VehicleManager::deleteVehicle() {
    int id;
    std::cout << "Enter ID of vehicle to delete: ";
    std::cin >> id; std::cin.ignore();

    std::stringstream query;
    query << "DELETE FROM Vehicles WHERE ID=" << id << ";";

    if (dbManager.executeQuery(query.str())) {
        std::cout << "Vehicle deleted successfully.\n";
    }
}

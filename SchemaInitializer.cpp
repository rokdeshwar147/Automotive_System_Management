#include "SchemaInitializer.h"
#include <iostream>

SchemaInitializer::SchemaInitializer(DatabaseManager& db) : dbManager(db) {}

void SchemaInitializer::initialize() {
    const std::string createVehiclesTable = R"(
        CREATE TABLE IF NOT EXISTS Vehicles (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            Make TEXT,
            Model TEXT,
            Year INTEGER,
            VIN TEXT UNIQUE,
            FuelType TEXT
        );
    )";

    const std::string createDTCsTable = R"(
        CREATE TABLE IF NOT EXISTS DTCs (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            VehicleID INTEGER,
            DTCCode TEXT,
            Description TEXT,
            Severity TEXT,
            FOREIGN KEY (VehicleID) REFERENCES Vehicles(ID)
        );
    )";

    const std::string createRealTimeTable = R"(
        CREATE TABLE IF NOT EXISTS RealTimeData (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            VehicleID INTEGER,
            Timestamp TEXT,
            EngineSpeed REAL,
            VehicleSpeed REAL,
            CoolantTemperature REAL,
            FuelLevel REAL,
            FOREIGN KEY (VehicleID) REFERENCES Vehicles(ID)
        );
    )";

    const std::string createAlertsTable = R"(
        CREATE TABLE IF NOT EXISTS Alerts (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            VehicleID INTEGER,
            Timestamp TEXT,
            AlertType TEXT,
            Description TEXT,
            FOREIGN KEY (VehicleID) REFERENCES Vehicles(ID)
        );
    )";

    const std::string createUsersTable = R"(
        CREATE TABLE IF NOT EXISTS Users (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            Username TEXT UNIQUE,
            Password TEXT,
            Role TEXT
        );
    )";

    if (dbManager.executeQuery(createVehiclesTable) &&
        dbManager.executeQuery(createDTCsTable) &&
        dbManager.executeQuery(createRealTimeTable) &&
        dbManager.executeQuery(createAlertsTable) &&
        dbManager.executeQuery(createUsersTable)) {
        std::cout << "All required tables are verified or created.\n";
    } else {
        std::cerr << "Failed to initialize schema.\n";
    }
}

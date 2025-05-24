#include "RealTimeMonitor.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

RealTimeMonitor::RealTimeMonitor(DatabaseManager& db) : dbManager(db) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // seed random generator
}

void RealTimeMonitor::simulateAndLogData() {
    int vehicleID;
    std::cout << "Enter Vehicle ID to simulate real-time data for: ";
    std::cin >> vehicleID;
    std::cin.ignore();

    // Simulated data (randomized)
    int engineSpeed = rand() % 7000;        // 0 - 7000 RPM
    int vehicleSpeed = rand() % 240;        // 0 - 240 km/h
    float coolantTemp = 60 + rand() % 60;   // 60 - 120°C
    float fuelLevel = static_cast<float>(rand() % 101); // 0 - 100 %

    // Timestamp
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string timestamp(dt);
    timestamp.pop_back(); // remove newline

    std::stringstream query;
    query << "INSERT INTO RealTimeData (VehicleID, Timestamp, EngineSpeed, VehicleSpeed, CoolantTemperature, FuelLevel) VALUES ("
          << vehicleID << ", "
          << "'" << timestamp << "', "
          << engineSpeed << ", "
          << vehicleSpeed << ", "
          << coolantTemp << ", "
          << fuelLevel << ");";

    if (dbManager.executeQuery(query.str())) {
        std::cout << "Simulated real-time data logged successfully.\n";
        std::cout << "Engine Speed: " << engineSpeed << " RPM\n";
        std::cout << "Vehicle Speed: " << vehicleSpeed << " km/h\n";
        std::cout << "Coolant Temp: " << coolantTemp << " °C\n";
        std::cout << "Fuel Level: " << fuelLevel << " %\n";
    } else {
        std::cerr << "Failed to log real-time data.\n";
    }
}

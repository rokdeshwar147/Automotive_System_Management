#include "DatabaseManager.h"
#include "VehicleManager.h"
#include "DTCManager.h"
#include "RealTimeMonitor.h"
#include "AlertManager.h"
#include "AnalyticsManager.h"
#include "UserManager.h"
#include "SchemaInitializer.h"
#include "ReportGenerator.h"




#include <iostream>

void showMenu() {
    std::cout << "\n--- Main Menu ---\n";
    std::cout << "0. Register New User\n";
    std::cout << "1. Add Vehicle\n";
    std::cout << "2. View Vehicles\n";
    std::cout << "3. Update Vehicle\n";
    std::cout << "4. Delete Vehicle\n";
    std::cout << "5. Add DTC\n";
    std::cout << "6. View DTCs\n";
    std::cout << "7. Update DTC\n";
    std::cout << "8. Delete DTC\n";
    std::cout << "9. Exit\n";
    std::cout << "10. Simulate & Log Real-Time Data\n";
    std::cout << "11. Check Real-Time Alerts\n";
    std::cout << "12. Check DTC Alerts\n";
     std::cout << "13. View Vehicle Performance Metrics\n";
    std::cout << "14. View Most Frequent DTCs\n";
        std::cout << "15. View Full Report\n";
    std::cout << "16. Export Report to File\n";

    std::cout << "Choose option: ";
}


int main() {
    DatabaseManager dbManager("automotive_system.db");

    if (!dbManager.open()) {
        std::cerr << "Failed to open database.\n";
        return -1;
    }

      SchemaInitializer schema(dbManager);
    schema.initialize();

    VehicleManager vehicleManager(dbManager);
    DTCManager dtcManager(dbManager);
     RealTimeMonitor rtMonitor(dbManager);
     AlertManager alertManager(dbManager);
      AnalyticsManager analytics(dbManager);
       UserManager userManager(dbManager);
       ReportGenerator reportGen(dbManager);
     sqlite3* db = dbManager.getDB();
    sqlite3_stmt* stmt;

    int userCount = 0;

    std::string userCheck = "SELECT COUNT(*) FROM Users;";
    if (sqlite3_prepare_v2(db, userCheck.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            userCount = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    if (userCount == 0) {
        std::cout << "No users found. Please register an admin user.\n";
        userManager.registerUser();
    }

    std::cout << "--- Login Required ---\n";
    if (!userManager.loginUser()) {
        std::cout << "Access denied.\n";
        return 1;
    }

    


    while (true) {
        showMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            std::cout << "0. Register New User\n";
            case 0: userManager.registerUser(); break;
            case 1: vehicleManager.addVehicle(); break;
            case 2: vehicleManager.viewVehicles(); break;
            case 3: vehicleManager.updateVehicle(); break;
            case 4: vehicleManager.deleteVehicle(); break;
            case 5: dtcManager.addDTC(); break;
            case 6: dtcManager.viewDTCs(); break;
            case 7: dtcManager.updateDTC(); break;
            case 8: dtcManager.deleteDTC(); break;
            case 9: dbManager.close(); return 0;
            case 10: rtMonitor.simulateAndLogData(); break;
            case 11: alertManager.checkForRealTimeAlerts(); break;
            case 12: alertManager.checkForDTCAlerts(); break;
            case 13: analytics.showVehiclePerformanceMetrics(); break;
            case 14: analytics.showFrequentDTCs(); break;
            
    case 15: reportGen.generateConsoleReport(); break;
    case 16: {
        std::string file;
        std::cout << "Enter filename (e.g., report.txt): ";
        std::getline(std::cin, file);
        reportGen.exportReportToFile(file);
        break;
    }
            
            default: std::cout << "Invalid choice.\n";
        }
    }


}

#include "DatabaseManager.h"
#include "VehicleManager.h"
#include "DTCManager.h"
#include "RealTimeMonitor.h"
#include "AlertManager.h"
#include "AnalyticsManager.h"
#include "UserManager.h"


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
    std::cout << "Choose option: ";
}


int main() {
    DatabaseManager dbManager("automotive_system.db");

    if (!dbManager.open()) {
        std::cerr << "Failed to open database.\n";
        return -1;
    }

    VehicleManager vehicleManager(dbManager);
    DTCManager dtcManager(dbManager);
     RealTimeMonitor rtMonitor(dbManager);
     AlertManager alertManager(dbManager);
      AnalyticsManager analytics(dbManager);
       UserManager userManager(dbManager);
    
    int initChoice = -1;

    // Loop until valid choice (0 = Register, 1 = Login)
    while (true) {
        std::cout << "Welcome! Please select an option:\n";
        std::cout << "0 - Register New User\n";
        std::cout << "1 - Login\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> initChoice)) {
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter 0 or 1.\n";
            continue;
        }

        if (initChoice == 0) {
            userManager.registerUser();
            // After registration, you might want to allow login or auto-login
            std::cout << "Please login to continue.\n";
            // Fall through to login prompt
            initChoice = 1; 
        }

        if (initChoice == 1) {
            std::cout << "--- Login Required ---\n";
            if (userManager.loginUser()) {
                break; // Successful login, proceed
            } else {
                std::cout << "Access denied. Try again.\n";
                // Optionally, limit login attempts or provide option to register again
            }
        } else {
            std::cout << "Invalid choice. Please enter 0 to Register or 1 to Login.\n";
        }
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
            default: std::cout << "Invalid choice.\n";
        }
    }


}

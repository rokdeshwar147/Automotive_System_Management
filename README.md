Automotive System Management
A modular C++ application designed to manage and monitor various aspects of automotive systems, including diagnostics, real-time monitoring, user management, and reporting.

🚗 Project Overview
The Automotive System Management project aims to provide a comprehensive solution for automotive diagnostics and management. It encompasses functionalities such as:
1) Diagnostic Trouble Code (DTC) Management
2) Real-Time Monitoring of Vehicle Parameters
3) User and Vehicle Management
4) Alert Notifications
5) Data Analytics and Reporting
6) Database Schema Initialization and Management

🛠️ System Features
1)Modular Architecture: Each component is encapsulated within its own class, promoting scalability and maintainability.
2)Database Integration: Utilizes SQL for persistent storage of vehicle data, user information, and diagnostic records.
3)Real-Time Monitoring: Continuously monitors vehicle parameters to detect anomalies and trigger alerts.
4)User Management: Handles authentication, authorization, and user-specific data access.
5)Comprehensive Reporting: Generates detailed reports based on collected data and analytics.

📁 Project Structure
Automotive_System_Management/
├── build/
├── AlertManager.cpp
├── AlertManager.h
├── AnalyticsManager.cpp
├── AnalyticsManager.h
├── CMakeLists.txt
├── DTCManager.cpp
├── DTCManager.h
├── DatabaseManager.cpp
├── DatabaseManager.h
├── RealTimeMonitor.cpp
├── RealTimeMonitor.h
├── ReportGenerator.cpp
├── ReportGenerator.h
├── SchemaInitializer.cpp
├── SchemaInitializer.h
├── UserManager.cpp
├── UserManager.h
├── VehicleManager.cpp
├── VehicleManager.h
├── main.cpp
├── sql/
└── README.md

📦 User Guide
To use the system:
• Build the project using CMake and make
• Launch the app from the terminal
• Select options from the console menu
• Insert, update, or analyze data as needed
• Monitor alerts and diagnostics
• Exit safely from the menu


🧰 Getting Started-> C++17
-> C++
-> CMake
-> SQLite or another SQL-compatible database

Steps:
1. Install dependencies
2. Run cmake . in the root directory
3. Run make to build the project
4. Run the output binary
5. For testing, compile and run the test_cases.cpp

🧪 Testing
Note: Testing instructions and frameworks are not specified in the repository. It's recommended to implement unit tests using frameworks like Google Test to ensure code reliability.

🤝 Contributing
Feel Free to contribute to our project it is an opensource Project.
Fixing Bug leads to efficient system run.

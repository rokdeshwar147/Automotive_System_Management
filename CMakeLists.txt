cmake_minimum_required(VERSION 3.10)
project(AutomotiveSystem)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include current directory for headers
include_directories(${CMAKE_SOURCE_DIR})

# Build SQLite from source
add_library(sqlite3 STATIC sqlite3.c)

# Build the main application
add_executable(init_database
    main.cpp
    DatabaseManager.cpp
    VehicleManager.cpp
    DTCManager.cpp
    RealTimeMonitor.cpp
    AlertManager.cpp
     AnalyticsManager.cpp
     UserManager.cpp

)

# Link SQLite with the app
target_link_libraries(init_database sqlite3)

cmake_minimum_required(VERSION 3.10)
project(AutomotiveSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

add_library(sqlite3 STATIC sqlite3.c)

add_executable(init_database
    main.cpp
    DatabaseManager.cpp
     SchemaInitializer.cpp
    VehicleManager.cpp
    DTCManager.cpp
    RealTimeMonitor.cpp
    AlertManager.cpp
     AnalyticsManager.cpp
     UserManager.cpp
     ReportGenerator.cpp


)

target_link_libraries(init_database sqlite3)

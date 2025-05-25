#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include "DatabaseManager.h"
#include <string>

class ReportGenerator {
private:
    DatabaseManager& dbManager;

public:
    ReportGenerator(DatabaseManager& db);
    void generateConsoleReport();
    void exportReportToFile(const std::string& filename);
};

#endif // REPORT_GENERATOR_H

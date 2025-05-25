#ifndef SCHEMA_INITIALIZER_H
#define SCHEMA_INITIALIZER_H

#include "DatabaseManager.h"

class SchemaInitializer {
private:
    DatabaseManager& dbManager;

public:
    SchemaInitializer(DatabaseManager& db);
    void initialize();
};

#endif

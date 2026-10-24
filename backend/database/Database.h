#pragma once
#include <string>
#include <sqlite3.h>

class Database {
private:
    sqlite3* db;
public:
    Database(const std::string& dbPath);
    ~Database();
    bool executeQuery(const std::string& query);
    sqlite3* getDbHandle() const { return db; }
};

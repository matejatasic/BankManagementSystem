#pragma once
#include <string>
#include <sqlite3.h>

class Repository {
    protected:
        sqlite3 *db;
        sqlite3_stmt* stmt;
        int result;
        void prepare_query(std::string query);
};
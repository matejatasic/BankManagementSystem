#pragma once
#include <string>
#include <sqlite3.h>

class Repository {
    protected:
        sqlite3 *db;
        sqlite3_stmt* stmt;
        int result;
        bool table_exists(std::string table_name);
        void prepare_query(std::string query);
};
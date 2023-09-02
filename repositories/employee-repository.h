#pragma once
#include <sqlite3.h>
#include <string>
#include <memory>
#include <vector>
#include "../models/employee-model.h"

class  EmployeeRepository {
    private:
        sqlite3 *db;
        sqlite3_stmt* stmt;
        int result;
        bool table_exists();
        std::shared_ptr<Employee> employee;
        std::string const table_name = "employees";
    public:
        EmployeeRepository(std::shared_ptr<Employee> employee);
        ~EmployeeRepository();
        std::vector<Employee> get_all();
        std::shared_ptr<Employee> find_by_name(std::string name);
};
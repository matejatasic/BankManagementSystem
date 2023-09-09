#pragma once
#include <sqlite3.h>
#include <string>
#include <memory>
#include <vector>
#include "./repository.h"
#include "../models/employee-model.h"

class  EmployeeRepository: Repository {
    private:
        bool table_exists();
        void prepare_query(std::string query);
        std::shared_ptr<Employee> employee;
        std::string const table_name = "employees";
    public:
        EmployeeRepository(std::shared_ptr<Employee> employee);
        ~EmployeeRepository();
        std::vector<Employee> get_all();
        void create(
            std::string username,
            std::string password,
            std::string phone,
            std::string position
        );
        void update(
            int id,
            std::string username,
            std::string password,
            std::string phone,
            std::string position
        );
        void destroy(int id);
        std::shared_ptr<Employee> find_by_username(std::string name);
};
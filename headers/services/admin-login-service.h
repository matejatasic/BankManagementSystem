#pragma once
#include <memory>
#include "../repositories/employee-repository.h"
#include "../models/employee-model.h"

class AdminLoginService {
    private:
        const std::string INVALID_NAME_ERROR_MESSAGE = "Name does not exist";
        const std::string INVALID_PASSWORD_ERROR_MESSAGE = "Password is invalid";
        const std::string DEFAULT_DATABASE_ERROR_MESSAGE = "There was a database error";
        std::shared_ptr<EmployeeRepository> employee_repository;
        std::shared_ptr<Employee> employee;
        std::string error_message = "";
    public:
        AdminLoginService(std::shared_ptr<EmployeeRepository>);
        void login(std::string username, std::string password);
        std::string get_error_message();
        std::shared_ptr<Employee> get_employee();
};
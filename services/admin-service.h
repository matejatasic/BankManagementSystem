#pragma once
#include <vector>
#include "../repositories/employee-repository.h"
#include "../repositories/account-repository.h"
#include "../services/hash-service.h"

class AdminService {
    private:
        std::shared_ptr<EmployeeRepository> employee_repository;
        std::shared_ptr<Employee> employee;
        std::shared_ptr<AccountRepository> account_repository;
        std::shared_ptr<Account> account;
        std::shared_ptr<HashService> hash_service;
    public:
        AdminService(
            std::shared_ptr<EmployeeRepository> employee_repository,
            std::shared_ptr<Employee> employee,
            std::shared_ptr<AccountRepository> account_repository,
            std::shared_ptr<Account> account,
            std::shared_ptr<HashService> hash_service
        );
        std::vector<Account> get_all_accounts();
        std::vector<Employee> get_all_employees();
        std::string get_account_details(std::string name);
};
#pragma once
#include <vector>
#include "../repositories/employee-repository.h"
#include "../repositories/account-repository.h"
#include "../repositories/transaction-repository.h"
#include "../services/hash-service.h"

class AdminService {
        std::shared_ptr<EmployeeRepository> employee_repository;
        std::shared_ptr<Employee> employee;
        std::shared_ptr<AccountRepository> account_repository;
        std::shared_ptr<Account> account;
        std::shared_ptr<TransactionRepository> transaction_repository;
        std::shared_ptr<HashService> hash_service;
    public:
        AdminService(
            std::shared_ptr<EmployeeRepository> employee_repository,
            std::shared_ptr<Employee> employee,
            std::shared_ptr<AccountRepository> account_repository,
            std::shared_ptr<Account> account,
            std::shared_ptr<TransactionRepository> transaction_repository,
            std::shared_ptr<HashService> hash_service
        );
        std::vector<Account> get_all_accounts();
        std::vector<Employee> get_all_employees();
        std::shared_ptr<Account> get_account(std::string owner_name);
        std::shared_ptr<Employee> get_employee(std::string username);
        std::vector<Transaction> get_transactions(int account_id);
        std::string get_account_details(std::string name);
        std::string get_employee_details(std::string username);
        std::string create_account(
            std::string owner,
            std::string pin,
            std::string phone,
            std::string email
        );
        std::string update_account(
            int id,
            std::string owner,
            std::string pin,
            std::string phone,
            std::string email
        );
        std::string delete_account(std::string owner);
        std::string create_employee(
            std::string username,
            std::string password,
            std::string phone,
            std::string position
        );
        std::string update_employee(
            int id,
            std::string username,
            std::string password,
            std::string phone,
            std::string position
        );
        std::string get_account_transactions_details(std::string owner);
};
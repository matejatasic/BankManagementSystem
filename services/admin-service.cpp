#include "./admin-service.h"

using namespace std;

AdminService::AdminService(
    shared_ptr<EmployeeRepository> employee_repository,
    shared_ptr<Employee> employee,
    shared_ptr<AccountRepository> account_repository,
    shared_ptr<Account> account,
    shared_ptr<HashService> hash_service
) {
    this->employee_repository = employee_repository;
    this-> employee = employee;
    this->account_repository = account_repository;
    this->account = account;
    this->hash_service = hash_service;
};

vector<Account> AdminService::get_all_accounts() {
    try {
        vector<Account> accounts = this->account_repository->get_all();

        return accounts;
    }
    catch(exception) {
        return {};
    }
}

vector<Employee> AdminService::get_all_employees() {
    try {
        vector<Employee> employees = this->employee_repository->get_all();

        return employees;
    }
    catch(exception) {
        return {};
    }
}


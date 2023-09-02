#include "./admin-service.h"
#include "../errors/errors.h"

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

string AdminService::get_account_details(string name) {
    try {
        shared_ptr<Account> account = this->account_repository->find_by_owner(name);

        return "Name: " + account->get_owner() + "\n"
        + "Pin: " + account->get_pin() + "\n"
        + "Phone: " + account->get_phone() + "\n"
        + "Email: " + account->get_email() + "\n"
        + "Registration date: " + account->get_registration_date() + "\n"
        + "Balance: " + to_string(account->get_balance()) + "\n";
    }
    catch(RecordNotFound) {
        return "The account with that owner does not exist";
    }
    catch(exception) {
        return "There was an error while getting the account details";
    }
}

string AdminService::get_employee_details(string username) {
    try {
        shared_ptr<Employee> employee = this->employee_repository->find_by_username(username);

        return "Username: " + employee->get_username() + "\n"
        + "Password: " + employee->get_password() + "\n"
        + "Phone: " + employee->get_phone() + "\n"
        + "Position: " + employee->get_position() + "\n";
    }
    catch(RecordNotFound) {
        return "The employee with that username does not exist";
    }
    catch(exception) {
        return "There was an error while getting the employee details";
    }
}

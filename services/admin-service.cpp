#include <iostream>
#include <chrono>
#include <ctime>
#include "./admin-service.h"
#include "../errors/errors.h"

using namespace std;

AdminService::AdminService(
    shared_ptr<EmployeeRepository> employee_repository,
    shared_ptr<Employee> employee,
    shared_ptr<AccountRepository> account_repository,
    shared_ptr<Account> account,
    shared_ptr<TransactionRepository> transaction_repository,
    shared_ptr<HashService> hash_service
) {
    this->employee_repository = employee_repository;
    this-> employee = employee;
    this->account_repository = account_repository;
    this->account = account;
    this->transaction_repository = transaction_repository;
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
        shared_ptr<Account> account = this->get_account(name);

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

shared_ptr<Account> AdminService::get_account(string owner) {
    return this->account_repository->find_by_owner(owner);
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

shared_ptr<Employee> AdminService::get_employee(string username) {
    return this->employee_repository->find_by_username(username);
}

string AdminService::create_account(
    string name,
    string pin,
    string phone,
    string email
) {
    time_t raw_time;
    std::tm* time_info;
    char registration_date [80];

    std::time(&raw_time);
    time_info = std::localtime(&raw_time);
    std::strftime(registration_date,80,"%Y-%m-%d",time_info);

    string hashed_pin = to_string(this->hash_service->hash(pin));

    try {
        this->account_repository->create(name, hashed_pin, phone, email, registration_date, 0);

        return "Account successfully created";
    }
    catch(CreateException) {
        return "There was a problem while creating the account";
    }
    catch(exception) {
        return "There was a problem while connecting to the database";
    }
}

string AdminService::update_account(
    int id,
    string name,
    string pin,
    string phone,
    string email
) {
    string hashed_pin = to_string(this->hash_service->hash(pin));

    try {
        this->account_repository->update(account->get_id(), name, hashed_pin, phone, email);

        return "Account successfully updated";
    }
    catch(UpdateException) {
        return "There was a problem while updating the account";
    }
    catch(exception) {
        return "There was a problem while connecting to the database";
    }
}

string AdminService::delete_account(string owner) {
    try {
        shared_ptr<Account> account = this->account_repository->find_by_owner(owner);

        this->account_repository->destroy(account->get_id());

        return "Successfully deleted the account";
    }
    catch(RecordNotFound) {
        return "The account with that owner does not exist";
    }
    catch(DeleteException) {
        return "There was a problem while trying to delete the account";
    }
    catch(exception) {
        return "There was a problem while connecting to the database";
    }
}

string AdminService::create_employee(
    string username,
    string password,
    string phone,
    string position
) {
    string hashed_password = to_string(this->hash_service->hash(password));

    try {
        this->employee_repository->create(username, hashed_password, phone, position);

        return "Employee successfully created";
    }
    catch(CreateException) {
        return "There was a problem while creating the employee";
    }
    catch(exception) {
        return "There was a problem while connecting to the database";
    }
}

string AdminService::update_employee(
    int id,
    string username,
    string password,
    string phone,
    string position
) {
    string hashed_password = to_string(this->hash_service->hash(password));

    try {
        this->employee_repository->update(
            id,
            username,
            hashed_password,
            phone,
            position
        );

        return "Employee successfully updated";
    }
    catch(UpdateException) {
        return "There was a problem while updating the employee";
    }
    catch(exception) {
        return "There was a problem while connecting to the database";
    }
}

string AdminService::delete_employee(string username) {
    try {
        shared_ptr<Employee> employee = this->employee_repository->find_by_username(username);

        this->employee_repository->destroy(employee->get_id());

        return "Successfully deleted the employee";
    }
    catch(RecordNotFound) {
        return "The employee with that username does not exist";
    }
    catch(DeleteException) {
        return "There was a problem while trying to delete the employee";
    }
    catch(exception) {
        return "There was a problem while connecting to the database";
    }
}

string AdminService::get_account_transactions_details(string owner) {
    try {
        shared_ptr<Account> account = this->account_repository->find_by_owner(owner);

        vector<Transaction> transactions = this->get_transactions(account->get_id());

        if (transactions.size() == 0) {
            return "This account has no transactions";
        }

        string result = "";

        for (Transaction transaction : transactions)
        {
            result += "Type: " + transaction.get_type() + "\n";
            result += "Amount: " + to_string(transaction.get_amount()) + "\n";
            result += "Datetime: " + transaction.get_datetime() + "\n\n";
        }

        return result;
    }
    catch(RecordNotFound) {
        return "The account with that owner does not exist";
    }
    catch(exception) {
        return "There was a problem while connecting to the database";
    }
}

vector<Transaction> AdminService::get_transactions(int account_id) {
    return this->transaction_repository->find_by_account_id(account_id);
}

#include <iostream>
#include "admin-login-service.h"
#include "../errors/errors.h"

using namespace std;

AdminLoginService::AdminLoginService(shared_ptr<EmployeeRepository> employee_repository) {
    this->employee_repository = employee_repository;
}

void AdminLoginService::login(string username, string password) {
    try {
        this->employee = this->employee_repository->find_by_username(username);

        if(this->employee->get_password() != password) {
            this->error_message = this->INVALID_PASSWORD_ERROR_MESSAGE;

            return;
        }
    }
    catch(RecordNotFound) {
        this->error_message = this->INVALID_PASSWORD_ERROR_MESSAGE;
    }
    catch(exception) {
        this->error_message = this->DEFAULT_DATABASE_ERROR_MESSAGE;
    }
}

string AdminLoginService::get_error_message() {
    return this->error_message;
}

shared_ptr<Employee> AdminLoginService::get_employee() {
    return this->employee;
}
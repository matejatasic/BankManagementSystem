#include <iostream>
#include <string>
#include <memory>
#include "repositories/transaction-repository.h"
#include "controllers/customer-controller.h"
#include "controllers/admin-controller.h"
#include "controllers/admin-login-controller.h"
#include "controllers/customer-login-controller.h"
#include "services/customer-service.h"
#include "services/hash-service.h"

using namespace std;

int get_mode();
shared_ptr<LoginController> get_login_controller(int choice);
shared_ptr<BankController> get_bank_controller(int choice);

const int CUSTOMER_MODE_CHOICE = 1;
const int ADMIN_MODE_CHOICE = 2;

int main()
{
    cout << "\n\n----------------------\n";
    cout << "BANK MANAGEMENT SYSTEM";
    cout << "\n----------------------\n\n";

    int mode = get_mode();

    shared_ptr<HashService> hash_service = make_shared<HashService>();

    if (mode != CUSTOMER_MODE_CHOICE && mode != ADMIN_MODE_CHOICE) {
        cout << "Invalid mode" << endl;

        return 1;
    }

    shared_ptr<LoginController> login_controller = get_login_controller(mode);
    shared_ptr<BankController> bank_controller = get_bank_controller(mode);

    login_controller->login();

    if (login_controller->get_error_message().length() > 0) {
        cout << login_controller->get_error_message() << endl;

        return 1;
    }

    bank_controller->run_app();

    return 0;
}

int get_mode() {
    int choice;

    cout << CUSTOMER_MODE_CHOICE << ": Customer mode" << endl;
    cout << ADMIN_MODE_CHOICE << ": Admin mode" << endl;
    cout << "\n";

    cout << "Choose mode: " ;
    cin >> choice;
    cout << "\n";

    return choice;
}

 shared_ptr<LoginController> get_login_controller(int choice) {
    if (choice == ADMIN_MODE_CHOICE) {
        shared_ptr<Employee> employee = make_shared<Employee>();
        shared_ptr<EmployeeRepository> employee_repository = make_shared<EmployeeRepository>(employee);
        shared_ptr<AdminLoginService> admin_login_service = make_shared<AdminLoginService>(employee_repository);
        shared_ptr<HashService> hash_service = make_shared<HashService>();

        shared_ptr<AdminLoginController> admin_login_controller = make_shared<AdminLoginController>(admin_login_service, hash_service);

        return admin_login_controller;
    }

    shared_ptr<Account> account = make_shared<Account>();
    shared_ptr<AccountRepository> account_repository = make_shared<AccountRepository>(account);
    shared_ptr<CustomerLoginService> customer_login_service = make_shared<CustomerLoginService>(account_repository);
    shared_ptr<HashService> hash_service = make_shared<HashService>();
    shared_ptr<CustomerLoginController> customer_login_controller = make_shared<CustomerLoginController>(customer_login_service, hash_service);

    return customer_login_controller;
}

 shared_ptr<BankController> get_bank_controller(int choice) {
    if (choice == ADMIN_MODE_CHOICE) {
        shared_ptr<Employee> employee = make_shared<Employee>();
        shared_ptr<EmployeeRepository> employee_repository = make_shared<EmployeeRepository>(employee);
        shared_ptr<Account> account = make_shared<Account>();
        shared_ptr<AccountRepository> account_repository = make_shared<AccountRepository>(account);
        shared_ptr<TransactionRepository> transaction_repository = make_shared<TransactionRepository>();
        shared_ptr<HashService> hash_service = make_shared<HashService>();
        shared_ptr<AdminService> admin_service = make_shared<AdminService>(
            employee_repository,
            employee,
            account_repository,
            account,
            transaction_repository,
            hash_service
        );

         shared_ptr<AdminController> admin_controller = make_shared<AdminController>(admin_service);

        return admin_controller;
    }

    shared_ptr<Account> account = make_shared<Account>();
    shared_ptr<AccountRepository> account_repository = make_shared<AccountRepository>(account);
    shared_ptr<CustomerLoginService> customer_login_service = make_shared<CustomerLoginService>(account_repository);
    shared_ptr<TransactionRepository> transaction_repository = make_shared<TransactionRepository>();
    shared_ptr<Transaction> transaction = make_shared<Transaction>();
    shared_ptr<HashService> hash_service = make_shared<HashService>();
    shared_ptr<CustomerService> customer_service = make_shared<CustomerService>(
        account_repository,
        transaction_repository,
        account,
        transaction,
        hash_service
    );

    shared_ptr<CustomerController> customer_controller = make_shared<CustomerController>(customer_service);

    return customer_controller;
}

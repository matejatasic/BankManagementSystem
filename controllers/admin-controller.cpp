#include <iostream>
#include "../headers/controllers/admin-controller.h"
#include "../headers/models/account-model.h"
#include "../headers/errors/errors.h"

using namespace std;

const string AdminController::TEXT_ALL_ACCOUNTS = "Show All Accounts";
const string AdminController::TEXT_ALL_EMPLOYEES = "Show All Employees";
const string AdminController::TEXT_SHOW_ACCOUNT = "Show Account Details";
const string AdminController::TEXT_SHOW_EMPLOYEE = "Show Employee Details";
const string AdminController::TEXT_CREATE_ACCOUNT = "Create Account";
const string AdminController::TEXT_UPDATE_ACCOUNT = "Update Account";
const string AdminController::TEXT_DELETE_ACCOUNT = "Delete Account";
const string AdminController::TEXT_CREATE_EMPLOYEE = "Create Employee";
const string AdminController::TEXT_UPDATE_EMPLOYEE = "Update Eployee";
const string AdminController::TEXT_DELETE_EMPLOYEE = "Delete Employee";
const string AdminController::TEXT_SHOW_ACCOUNT_TRANSACTIONS = "Show Account Transactions";
const string AdminController::TEXT_EXIT = "Exit";

AdminController::AdminController(std::shared_ptr<AdminService> admin_service) {
    this->admin_service = admin_service;
}

void AdminController::run_app() {
    int choice = 0;

    while(true)
    {
        this->show_menu();

        cout << "\nYour choice: ";
        cin >> choice;
        cout << "\n";

        switch(choice)
        {
            case this->CHOICE_ALL_ACCOUNTS:
                this->show_all_accounts();
                break;
            case this->CHOICE_ALL_EMPLOYEES:
                this->show_all_employees();
                break;
            case this->CHOICE_SHOW_ACCOUNT:
                this->show_account_details();
                break;
            case this->CHOICE_SHOW_EMPLOYEE:
                this->show_employee_details();
                break;
            case this->CHOICE_CREATE_ACCOUNT:
                this->create_account();
                break;
            case this->CHOICE_UPDATE_ACCOUNT:
                this->update_account();
                break;
            case this->CHOICE_DELETE_ACCOUNT:
                this->delete_account();
                break;
            case this->CHOICE_CREATE_EMPLOYEE:
                this->create_employee();
                break;
            case this->CHOICE_UPDATE_EMPLOYEE:
                this->update_employee();
                break;
            case this->CHOICE_DELETE_EMPLOYEE:
                this->delete_employee();
                break;
            case this->CHOICE_SHOW_ACCOUNT_TRANSACTIONS:
                this->show_account_transactions();
                break;
            case this->CHOICE_EXIT:
                exit(0);
                break;
            default:
                cout << "Invalid Choice \n";
        }
    }
};

void AdminController::show_menu() {
    this->show_header("MENU");

    cout << this->CHOICE_ALL_ACCOUNTS << ": " << this->TEXT_ALL_ACCOUNTS << endl;
    cout << this->CHOICE_ALL_EMPLOYEES << ": " << this->TEXT_ALL_EMPLOYEES << endl;
    cout << this->CHOICE_SHOW_ACCOUNT << ": " << this->TEXT_SHOW_ACCOUNT << endl;
    cout << this->CHOICE_SHOW_EMPLOYEE << ": " << this->TEXT_SHOW_EMPLOYEE << endl;
    cout << this->CHOICE_CREATE_ACCOUNT << ": " << this->TEXT_CREATE_ACCOUNT << endl;
    cout << this->CHOICE_UPDATE_ACCOUNT << ": " << this->TEXT_UPDATE_ACCOUNT << endl;
    cout << this->CHOICE_DELETE_ACCOUNT << ": " << this->TEXT_DELETE_ACCOUNT << endl;
    cout << this->CHOICE_CREATE_EMPLOYEE << ": " << this->TEXT_CREATE_EMPLOYEE << endl;
    cout << this->CHOICE_UPDATE_EMPLOYEE << ": " << this->TEXT_UPDATE_EMPLOYEE << endl;
    cout << this->CHOICE_DELETE_EMPLOYEE << ": " << this->TEXT_DELETE_EMPLOYEE << endl;
    cout << this->CHOICE_SHOW_ACCOUNT_TRANSACTIONS << ": " << this->TEXT_SHOW_ACCOUNT_TRANSACTIONS << endl;
    cout << this->CHOICE_EXIT << ": " << this->TEXT_EXIT << endl;
};

void AdminController::show_all_accounts() {
    this->show_header(this->TEXT_ALL_ACCOUNTS);

    vector<Account> accounts = this->admin_service->get_all_accounts();

    size_t employees_size = accounts.size();

    for (size_t i = 0; i < employees_size; i++) {
        // Show 5 accounts before prompting for a key press
        if (i != 0 && i % 5 == 0) {
            cout << "Shown " << i << " accounts of " << employees_size << endl;
            this->show_press_enter();
        }

        Account account = accounts[i];

        cout << "Id: " << account.get_id() << endl;
        cout << "Owner: " << account.get_owner() << endl;
        cout << "Pin: " << account.get_pin() << endl;
        cout << "Phone: " << account.get_phone() << endl;
        cout << "Email: " << account.get_email() << endl;
        cout << "Registration date: " << account.get_registration_date() << endl;
        cout << "Balance: " << account.get_balance() << endl;
        cout << "\n";
    }
}

void AdminController::show_all_employees() {
    this->show_header(this->TEXT_ALL_EMPLOYEES);

    vector<Employee> employees = this->admin_service->get_all_employees();

    size_t employees_size = employees.size();

    for (size_t i = 0; i < employees_size; i++) {
        // Show 5 accounts before prompting for a key press
        if (i != 0 && i % 5 == 0) {
            cout << "Shown " << i << " employees of " << employees_size << endl;
            this->show_press_enter();
        }

        Employee employee = employees[i];

        cout << "Id: " << employee.get_id() << endl;
        cout << "Owner: " << employee.get_username() << endl;
        cout << "Password: " << employee.get_password() << endl;
        cout << "Phone: " << employee.get_phone() << endl;
        cout << "Position: " << employee.get_position() << endl;
        cout << "\n";
    }
}

void AdminController::show_account_details() {
    this->show_header(this->TEXT_SHOW_ACCOUNT);

    string name;

    cout << "Type in the name of the owner: ";
    cin >> name;

    string result = this->admin_service->get_account_details(name);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::show_employee_details() {
    this->show_header(this->TEXT_SHOW_EMPLOYEE);

    string username;

    cout << "Type in the username of the employee: ";
    cin >> username;

    string result = this->admin_service->get_employee_details(username);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::create_account() {
    this->show_header(this->TEXT_CREATE_ACCOUNT);

    string name, pin, phone, email;

    cout << "Type in the name: ";
    cin >> name;
    cout << "Type in the pin: ";
    cin >> pin;
    cout << "Type in the phone: ";
    cin >> phone;
    cout << "Type in the email: ";
    cin >> email;

    string result = this->admin_service->create_account(name, pin, phone, email);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::update_account() {
    this->show_header(this->TEXT_UPDATE_ACCOUNT);

    string owner_name;

    cout << "Type in the owner: ";
    cin >> owner_name;

    shared_ptr<Account> account;

    try {
        account = this->admin_service->get_account(owner_name);
    }
    catch(RecordNotFound) {
        cout << "\n";
        cout << "Account with that owner does not exist" << endl;
        this->show_press_enter();

        return;
    }

    string name, pin, phone, email;

    cout << "Type in the name: ";
    cin >> name;
    cout << "Type in the pin: ";
    cin >> pin;
    cout << "Type in the phone: ";
    cin >> phone;
    cout << "Type in the email: ";
    cin >> email;

    string result = this->admin_service->update_account(
        account->get_id(),
        name,
        pin,
        phone,
        email
    );

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::delete_account() {
    this->show_header(this->TEXT_DELETE_ACCOUNT);

    string owner_name;

    cout << "Type in the owner: ";
    cin >> owner_name;

    string result = this->admin_service->delete_account(owner_name);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::create_employee() {
    this->show_header(this->TEXT_CREATE_EMPLOYEE);

    string username, password, phone, position;

    cout << "Type in the username: ";
    cin >> username;
    cout << "Type in the password: ";
    cin >> password;
    cout << "Type in the phone: ";
    cin >> phone;
    cout << "Type in the position: ";
    cin >> position;

    string result = this->admin_service->create_employee(username, password, phone, position);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::update_employee() {
    this->show_header(this->TEXT_UPDATE_EMPLOYEE);

    string username;

    cout << "Type in the username: ";
    cin >> username;

    shared_ptr<Employee> employee;

    try {
        employee = this->admin_service->get_employee(username);
    }
    catch(RecordNotFound) {
        cout << "\n";
        cout << "Employee with that username does not exist" << endl;
        this->show_press_enter();

        return;
    }

    string password, phone, position;

    cout << "Type in the username: ";
    cin >> username;
    cout << "Type in the password: ";
    cin >> password;
    cout << "Type in the phone: ";
    cin >> phone;
    cout << "Type in the position: ";
    cin >> position;

    string result = this->admin_service->update_employee(employee->get_id(), username, password, phone, position);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::delete_employee() {
    this->show_header(this->TEXT_DELETE_EMPLOYEE);

    string username;

    cout << "Type in the username: ";
    cin >> username;

    string result = this->admin_service->delete_employee(username);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::show_account_transactions() {
    this->show_header(this->TEXT_SHOW_ACCOUNT_TRANSACTIONS);

    string owner_name;

    cout << "Type in the owner: ";
    cin >> owner_name;

    string result = this->admin_service->get_account_transactions_details(owner_name);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::show_header(string header) {
    BankController::show_header(header);
}

void AdminController::show_press_enter() {
    BankController::show_press_enter();
};

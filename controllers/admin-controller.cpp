#include <iostream>
#include "./admin-controller.h"
#include "../models/account-model.h"
#include "../errors/errors.h"

using namespace std;

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
                break;
            case this->CHOICE_DELETE_EMPLOYEE:
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
    cout << "\nMENU\n";
    cout << "---------\n";

    cout << "\n" << this->CHOICE_ALL_ACCOUNTS << ": Show All Accounts";
    cout << "\n" << this->CHOICE_ALL_EMPLOYEES << ": Show All Employees";
    cout << "\n" << this->CHOICE_SHOW_ACCOUNT << ": Show Account Details";
    cout << "\n" << this->CHOICE_SHOW_EMPLOYEE << ": Show Employee Details";
    cout << "\n" << this->CHOICE_CREATE_ACCOUNT << ": Create Account";
    cout << "\n" << this->CHOICE_UPDATE_ACCOUNT << ": Update Account";
    cout << "\n" << this->CHOICE_DELETE_ACCOUNT << ": Delete Account";
    cout << "\n" << this->CHOICE_CREATE_EMPLOYEE << ": Create Employee";
    cout << "\n" << this->CHOICE_UPDATE_EMPLOYEE << ": Update Employee";
    cout << "\n" << this->CHOICE_DELETE_EMPLOYEE << ": Delete Employee";
    cout << "\n" << this->CHOICE_SHOW_ACCOUNT_TRANSACTIONS << ": Show Account Transactions";
    cout << "\n" << this->CHOICE_EXIT << ": Exit\n";
};

void AdminController::show_all_accounts() {
    cout << "\nShow All Accounts\n";
    cout << "-----------------\n\n";

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
    cout << "\nShow All Employees\n";
    cout << "-----------------\n\n";

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
    cout << "\nShow Account Details\n";
    cout << "-----------------\n\n";

    string name;

    cout << "Type in the name of the owner: ";
    cin >> name;

    string result = this->admin_service->get_account_details(name);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::show_employee_details() {
    cout << "\nShow Employee Details\n";
    cout << "-----------------\n\n";

    string username;

    cout << "Type in the username of the employee: ";
    cin >> username;

    string result = this->admin_service->get_employee_details(username);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::create_account() {
    cout << "\nCreate Account\n";
    cout << "--------------\n\n";

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
    cout << "\nUpdate Account\n";
    cout << "--------------\n\n";

    string owner_name, name, pin, phone, email;


    cout << "Type in the owner: ";
    cin >> owner_name;

    shared_ptr<Account> account;

    try {
        account = this->admin_service->get_account(owner_name);
    }
    catch(RecordNotFound) {
        cout << "\n";
        cout << "Account with that owner does not exist";
        this->show_press_enter();

        return;
    }

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
    cout << "\nDelete Account\n";
    cout << "--------------\n\n";

    string owner_name;

    cout << "Type in the owner: ";
    cin >> owner_name;

    string result = this->admin_service->delete_account(owner_name);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::create_employee() {
    cout << "\nCreate Employee\n";
    cout << "--------------\n\n";

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

void AdminController::show_account_transactions() {
    cout << "\nShow Account Transactions\n";
    cout << "--------------------------\n\n";

    string owner_name;

    cout << "Type in the owner: ";
    cin >> owner_name;

    string result = this->admin_service->get_account_transactions_details(owner_name);

    cout << "\n";
    cout << result << endl;
    this->show_press_enter();
}

void AdminController::show_press_enter() {
    BankController::show_press_enter();
};

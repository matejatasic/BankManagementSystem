#include <iostream>
#include "./admin-controller.h"
#include "../models/account-model.h"

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
            case this->CHOICE_CREATE_ACCOUNT:
                break;
            case this->CHOICE_UPDATE_ACCOUNT:
                break;
            case this->CHOICE_DELETE_ACCOUNT:
                break;
            case this->CHOICE_VIEW_TRANSACTIONS:
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
    cout << "\n" << this->CHOICE_CREATE_ACCOUNT << ": Create Account";
    cout << "\n" << this->CHOICE_UPDATE_ACCOUNT << ": Update Account";
    cout << "\n" << this->CHOICE_DELETE_ACCOUNT << ": Delete Account";
    cout << "\n" << this->CHOICE_VIEW_TRANSACTIONS << ": View Transactions";
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

void AdminController::show_press_enter() {
    BankController::show_press_enter();
};

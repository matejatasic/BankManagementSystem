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

        switch(choice)
        {
            case this->CHOICE_ALL_ACCOUNTS:
                this->see_all_accounts();
                break;
            case this->CHOICE_FIND_ACCOUNT:
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

    cout << "\n" << this->CHOICE_ALL_ACCOUNTS << ": See All Accounts";
    cout << "\n" << this->CHOICE_FIND_ACCOUNT << ": Find Account";
    cout << "\n" << this->CHOICE_CREATE_ACCOUNT << ": Create Account";
    cout << "\n" << this->CHOICE_UPDATE_ACCOUNT << ": Update Account";
    cout << "\n" << this->CHOICE_DELETE_ACCOUNT << ": Delete Account";
    cout << "\n" << this->CHOICE_VIEW_TRANSACTIONS << ": View Transactions";
    cout << "\n" << this->CHOICE_EXIT << ": Exit\n";
};

void AdminController::see_all_accounts() {
    cout << "\nSee All Accounts\n";
    cout << "-----------------\n\n";

    vector<Account> accounts = this->admin_service->get_all_accounts();

    size_t accounts_size = accounts.size();

    for (size_t i = 0; i < accounts_size; i++)
    {
        // Show 5 accounts before prompting for a key press
        if (i != 0 && i % 5 == 0) {
            cout << "Shown " << i << " accounts of " << accounts_size << endl;
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

void AdminController::show_press_enter() {
    BankController::show_press_enter();
};

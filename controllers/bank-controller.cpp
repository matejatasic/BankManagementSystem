#include <iostream>
#include <cmath>
#include "bank-controller.h"
#include "../errors/errors.h"

using namespace std;

BankController::BankController(
    shared_ptr<BankService> bank_service
) {
    this->bank_service = bank_service;
}

void BankController::run_app() {
    int choice = 0;

    while(true)
    {
        this->show_menu();

        cout << "\nYour choice: ";
        cin >> choice;

        switch(choice)
        {
            case this->CHOICE_ACCOUNT_DETAILS:
                this->show_account_details();
                break;
            case this->CHOICE_DEPOSIT:
                this->deposit_money();
                break;
            case this->CHOICE_WITHDRAW:
                this->withdraw_money();
                break;
            case this->CHOICE_TRANSACTION:
                this->show_transaction_details();
                break;
            case this->CHOICE_CHANGE_PIN:
                this->change_pin();
                break;
            case this->CHOICE_CHANGE_PERSONAL_DETAILS:
                this->change_personal_details();
                break;
            case this->CHOICE_EXIT:
                exit(0);
                break;
            default:
                cout << "Invalid Choice \n";
        }
    }
}

void BankController::show_menu() {
    cout << "\nMENU\n";
    cout << "---------\n";

    cout << "\n" << this->CHOICE_ACCOUNT_DETAILS << ": Account Details";
    cout << "\n" << this->CHOICE_DEPOSIT << ": Deposit Money";
    cout << "\n" << this->CHOICE_WITHDRAW << ": Withdraw Money";
    cout << "\n" << this->CHOICE_TRANSACTION << ": Transaction Details";
    cout << "\n" << this->CHOICE_CHANGE_PIN << ": Change Pin";
    cout << "\n" << this->CHOICE_CHANGE_PERSONAL_DETAILS << ": Change Personal Details";
    cout << "\n" << this->CHOICE_EXIT << ": Exit\n";
}

void BankController::show_account_details() {
    cout << "\nAcount Details\n";
    cout << "--------------\n\n";

    string result = this->bank_service->show_account_details();

    cout << result;

    show_press_any_key();
}

void BankController::deposit_money() {
    cout << "\nDeposit Money\n";
    cout << "--------------\n\n";

    double amount = 0;

    cout << "Enter amount: ";
    cin >> amount;

    amount = floor(amount * 100.0) / 100.0;

    string result = this->bank_service->deposit_money(amount);

    cout << "\n";
    cout << result << endl;

    show_press_any_key();
}

void BankController::withdraw_money() {
    cout << "\nWithdraw Money\n";
    cout << "--------------\n\n";

    double amount = 0;

    cout << "Enter amount: ";
    cin >> amount;
    // round the number to two decimals
    amount = floor(amount * 100.0) / 100.0;

    string result = this->bank_service->withdraw_money(amount);

    cout << "\n";
    cout << result << endl;

    this->show_press_any_key();
}

void BankController::show_transaction_details() {
    cout << "\nTransaction details\n";
    cout << "--------------\n\n";

    string result = this->bank_service->show_transaction_details();

    cout << result << endl;

    this->show_press_any_key();
}

void BankController::change_pin() {
    cout << "\nChange pin\n";
    cout << "-----------\n\n";

    string old_pin;
    string new_pin;

    cout << "Enter your old pin: ";
    cin >> old_pin;

    cout << "Enter you new pin: ";
    cin >> new_pin;

    string result = this->bank_service->change_pin(old_pin, new_pin);

    cout << "\n";
    cout << result << endl;

    this->show_press_any_key();
}

void BankController::change_personal_details() {
    cout << "\nChange personal details\n";
    cout << "-------------------\n\n";

    string name;
    string phone;
    string email;

    cout << "Type in your name: ";
    cin >> name;

    cout << "Type in your phone: ";
    cin >> phone;

    cout << "Type in your email: ";
    cin >> email;

    string result = this->bank_service->change_personal_details(name, phone, email);

    cout << "\n";
    cout << result << endl;

    this->show_press_any_key();
}

void BankController::show_press_any_key() {
    cout << "\nPress Enter to continue… ";
    cin.get();
    cin.get();
}
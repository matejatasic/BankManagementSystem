#include <iostream>
#include <cmath>
#include "../headers/controllers/customer-controller.h"
#include "../headers/errors/errors.h"

using namespace std;

const string CustomerController::TEXT_ACCOUNT_DETAILS = "Account Details";
const string CustomerController::TEXT_DEPOSIT = "Deposit Money";
const string CustomerController::TEXT_WITHDRAW = "Withdraw Money";
const string CustomerController::TEXT_TRANSACTION = "Transaction Details";
const string CustomerController::TEXT_CHANGE_PIN = "Change Pin";
const string CustomerController::TEXT_CHANGE_PERSONAL_DETAILS = "Change Personal Details";
const string CustomerController::TEXT_EXIT = "Exit";

CustomerController::CustomerController(
    shared_ptr<CustomerService> customer_service
) {
    this->customer_service = customer_service;
}

void CustomerController::run_app() {
    int choice = 0;

    while(true)
    {
        this->show_menu();

        cout << "\nYour choice: ";
        cin >> choice;
        cout << "\n";

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

void CustomerController::show_menu() {
    this->show_header("MENU");

    cout << this->CHOICE_ACCOUNT_DETAILS << ": " << this->TEXT_ACCOUNT_DETAILS << endl;
    cout << this->CHOICE_DEPOSIT << ": " << this->TEXT_DEPOSIT << endl;
    cout << this->CHOICE_WITHDRAW << ": " << this->TEXT_WITHDRAW << endl;
    cout << this->CHOICE_TRANSACTION << ": " << this->TEXT_TRANSACTION << endl;
    cout << this->CHOICE_CHANGE_PIN << ": " << this->TEXT_CHANGE_PIN << endl;
    cout << this->CHOICE_CHANGE_PERSONAL_DETAILS << ": " << this->TEXT_CHANGE_PERSONAL_DETAILS << endl;
    cout << this->CHOICE_EXIT << ": " << this->TEXT_EXIT << endl;
}

void CustomerController::show_account_details() {
    this->show_header(this->TEXT_ACCOUNT_DETAILS);

    string result = this->customer_service->get_account_details();

    cout << result;

    show_press_enter();
}

void CustomerController::deposit_money() {
    this->show_header(this->TEXT_DEPOSIT);

    double amount = 0;

    cout << "Enter amount: ";
    cin >> amount;

    amount = floor(amount * 100.0) / 100.0;

    string result = this->customer_service->deposit_money(amount);

    cout << "\n";
    cout << result << endl;

    show_press_enter();
}

void CustomerController::withdraw_money() {
    this->show_header(this->TEXT_WITHDRAW);

    double amount = 0;

    cout << "Enter amount: ";
    cin >> amount;
    // round the number to two decimals
    amount = floor(amount * 100.0) / 100.0;

    string result = this->customer_service->withdraw_money(amount);

    cout << "\n";
    cout << result << endl;

    this->show_press_enter();
}

void CustomerController::show_transaction_details() {
    this->show_header(this->TEXT_TRANSACTION);

    string result = this->customer_service->show_transaction_details();

    cout << result << endl;

    this->show_press_enter();
}

void CustomerController::change_pin() {
    this->show_header(this->TEXT_CHANGE_PIN);

    string old_pin;
    string new_pin;

    cout << "Enter your old pin: ";
    cin >> old_pin;

    cout << "Enter you new pin: ";
    cin >> new_pin;

    string result = this->customer_service->change_pin(old_pin, new_pin);

    cout << "\n";
    cout << result << endl;

    this->show_press_enter();
}

void CustomerController::change_personal_details() {
    this->show_header(this->TEXT_CHANGE_PERSONAL_DETAILS);

    string name;
    string phone;
    string email;

    cout << "Type in your name: ";
    cin >> name;

    cout << "Type in your phone: ";
    cin >> phone;

    cout << "Type in your email: ";
    cin >> email;

    string result = this->customer_service->change_personal_details(name, phone, email);

    cout << "\n";
    cout << result << endl;

    this->show_press_enter();
}

void CustomerController::show_header(string header) {
    BankController::show_header(header);
}

void CustomerController::show_press_enter() {
    BankController::show_press_enter();
}
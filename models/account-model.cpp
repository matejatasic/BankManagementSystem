#include "../headers/models/account-model.h"

using namespace std;

Account::Account() {}
void Account::Init(
    int id,
    string owner,
    string pin,
    string phone,
    string email,
    string registration_date,
    double balance
) {
    this->id = id;
    this->owner = owner;
    this->pin = pin;
    this->phone = phone;
    this->email = email;
    this->registration_date = registration_date;
    this->balance = balance;
}

int Account::get_id() {
    return this->id;
}

string Account::get_owner() {
    return this->owner;
}

string Account::get_pin() {
    return this->pin;
}

string Account::get_phone() {
    return this->phone;
}

string Account::get_email() {
    return this->email;
}

string Account::get_registration_date() {
    return this->registration_date;
}

Account* Account::set_owner(string owner) {
    this->owner = owner;

    return this;
}

Account* Account::set_pin(string pin) {
    this->pin = pin;

    return this;
}

Account* Account::set_balance(double balance) {
    this->balance = balance;

    return this;
}

Account* Account::set_phone(std::string phone) {
    this->phone = phone;

    return this;
}

Account* Account::set_email(std::string email) {
    this->email = email;

    return this;
}

double Account::get_balance() {
    return this->balance;
}
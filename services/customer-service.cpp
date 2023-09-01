#include <iostream>
#include <cmath>
#include "customer-service.h"
#include "../errors/errors.h"

using namespace std;

CustomerService::CustomerService(
    shared_ptr<AccountRepository> account_repository,
    shared_ptr<TransactionRepository> transaction_repository,
    shared_ptr<Account> account,
    shared_ptr<Transaction> transaction,
    shared_ptr<HashService> hash_service
) {
    this->account_repository = account_repository;
    this->transaction_repository = transaction_repository;
    this->account = account;
    this->transaction = transaction;
    this->hash_service = hash_service;
}

string CustomerService::show_account_details() {
    cout << "\nAcount Details\n";
    cout << "--------------\n\n";

    return "Name: " + this->account->get_owner() + "\n"
    + "Pin: " + this->account->get_pin() + "\n"
    + "Phone: " + this->account->get_phone() + "\n"
    + "Email: " + this->account->get_email() + "\n"
    + "Registration date: " + this->account->get_registration_date() + "\n"
    + "Balance: " + to_string(this->account->get_balance()) + "\n";
}

string CustomerService::deposit_money(double amount) {
    try {
        this->account_repository->update_balance(amount);
        this->transaction->Init(amount, account->get_id(), "deposit");
        this->transaction_repository->create(*this->transaction);
        this->account->set_balance(this->account->get_balance() + amount);

        return "Successfully deposited";
    }
    catch(CreateException) {
        return "There was a problem while creating the transaction";
    }
    catch(UpdateException) {
        return "There was a problem while updating the balance";
    }
    catch(exception) {
        return "There was a problem while depositing";
    }
}

string CustomerService::withdraw_money(double amount) {
    if (amount > this->account->get_balance()) {
        return "Not enough money on the account";
    }

    try {
        this->account_repository->update_balance(-amount);
        this->transaction->Init(-amount, this->account->get_id(), "withdraw");
        this->transaction_repository->create(*this->transaction);
        this->account->set_balance(this->account->get_balance() - amount);

        return "Successfully withdrawn";
    }
    catch(CreateException) {
        return "There was a problem while creating the transaction";
    }
    catch(UpdateException) {
        return "There was a problem while updating the balance";
    }
    catch(exception) {
        return "There was a problem while withdrawing";
    }
}

string CustomerService::show_transaction_details() {
    try {
        vector<Transaction> transactions = this->transaction_repository->find_by_account_id(account->get_id());

        if(transactions.size() == 0) {
            cout << "No transactions";
        }

        string result = "";

        for(unsigned int i = 0; i < transactions.size(); i++) {
            result += "Type: " + transactions[i].get_type() + "\n";
            result += "Amount: " + to_string(transactions[i].get_amount()) + "\n";
            result += "Datetime: " + transactions[i].get_datetime() + "\n\n";
        }

        return result;
    }
    catch(exception) {
        return "There was a problem while fetching transactions";
    }
}

string CustomerService::change_pin(string old_pin, string new_pin) {
    old_pin = to_string(this->hash_service->hash(old_pin));

    if(old_pin != this->account->get_pin()) {
        return "Old pin is not valid";
    }

    try {
        new_pin = to_string(this->hash_service->hash(new_pin));

        this->account_repository->update_pin(new_pin);

        this->account->set_pin(new_pin);

        return "Successfully changed the pin";
    }
    catch(UpdateException) {
        return "There was a problem while updating the pin";
    }
    catch(exception) {
        return "There was a problem while changing the pin";
    }
}

string CustomerService::change_personal_details(
    string name,
    string phone,
    string email
) {
    try {
        this->account_repository->update_personal_details(name, phone, email);

        this->account->set_owner(name);
        this->account->set_phone(phone);
        this->account->set_email(email);

        return "Successfully changed the personal details";
    }
    catch(UpdateException) {
        return "There was a problem while updating the personal details";
    }
    catch(exception) {
        return "There was a problem while changing the personal details";
    }
}

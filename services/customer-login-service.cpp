#include "../headers/services/customer-login-service.h"
#include "../headers/errors/errors.h"

using namespace std;

CustomerLoginService::CustomerLoginService(shared_ptr<AccountRepository> account_repository) {
    this->account_repository = account_repository;
}

void CustomerLoginService::login(string name, string pin) {
    try {
        this->account = this->account_repository->find_by_owner(name);

        if(this->account->get_pin() != pin) {
            this->error_message = this->INVALID_PIN_ERROR_MESSAGE;

            return;
        }
    }
    catch(RecordNotFound) {
        this->error_message = this->INVALID_PIN_ERROR_MESSAGE;
    }
    catch(exception) {
        this->error_message = this->DEFAULT_DATABASE_ERROR_MESSAGE;
    }
}

string CustomerLoginService::get_error_message() {
    return this->error_message;
}

shared_ptr<Account> CustomerLoginService::get_account() {
    return this->account;
}
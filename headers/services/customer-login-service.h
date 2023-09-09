#pragma once
#include <memory>
#include "../repositories/account-repository.h"
#include "../models/account-model.h"

class CustomerLoginService {
    private:
        const std::string INVALID_NAME_ERROR_MESSAGE = "Name does not exist";
        const std::string INVALID_PIN_ERROR_MESSAGE = "Pin is invalid";
        const std::string DEFAULT_DATABASE_ERROR_MESSAGE = "There was a database error";
        std::shared_ptr<AccountRepository> account_repository;
        std::shared_ptr<Account> account;
        std::string error_message = "";
    public:
        CustomerLoginService(std::shared_ptr<AccountRepository>);
        void login(std::string name, std::string password);
        std::string get_error_message();
        std::shared_ptr<Account> get_account();
};
#pragma once
#include "../repositories/account-repository.h"
#include "../repositories/transaction-repository.h"
#include "../services/hash-service.h"

class CustomerService {
    private:
        std::shared_ptr<AccountRepository> account_repository;
        std::shared_ptr<TransactionRepository> transaction_repository;
        std::shared_ptr<Account> account;
        std::shared_ptr<Transaction> transaction;
        std::shared_ptr<HashService> hash_service;
    public:
        std::string show_account_details();
        std::string deposit_money(double amount);
        std::string withdraw_money(double amount);
        std::string show_transaction_details();
        std::string change_pin(std::string old_pin, std::string new_pin);
        std::string change_personal_details(
            std::string name,
            std::string phone,
            std::string email
        );
        CustomerService(
            std::shared_ptr<AccountRepository> account_repository,
            std::shared_ptr<TransactionRepository> transaction_repository,
            std::shared_ptr<Account> account,
            std::shared_ptr<Transaction> transaction,
            std::shared_ptr<HashService> hash_service
        );
};
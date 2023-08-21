#include "../repositories/account-repository.h"
#include "../repositories/transaction-repository.h"
#include "../services/hash-service.h"

class BankService {
    static const int CHOICE_ACCOUNT_DETAILS = 1;
    static const int CHOICE_DEPOSIT = 2;
    static const int CHOICE_WITHDRAW = 3;
    static const int CHOICE_TRANSACTION = 4;
    static const int CHOICE_CHANGE_PIN = 5;
    static const int CHOICE_EXIT = 6;

    private:
        std::shared_ptr<AccountRepository> account_repository;
        std::shared_ptr<TransactionRepository> transaction_repository;
        std::shared_ptr<Account> account;
        std::shared_ptr<Transaction> transaction;
        std::shared_ptr<HashService> hash_service;

        void show_menu();
        void show_account_details();
        void deposit_money();
        void withdraw_money();
        void show_transaction_details();
        void change_pin();
        void show_press_any_key();
    public:
        void run_app();
        BankService(
            std::shared_ptr<AccountRepository> account_repository,
            std::shared_ptr<TransactionRepository> transaction_repository,
            std::shared_ptr<Account> account,
            std::shared_ptr<Transaction> transaction,
            std::shared_ptr<HashService> hash_service
        );
};
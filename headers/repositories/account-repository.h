#pragma once
#include <sqlite3.h>
#include <string>
#include <memory>
#include <vector>
#include "./repository.h"
#include "../models/account-model.h"

class  AccountRepository: Repository {
    private:
        bool table_exists();
        void prepare_query(std::string query);
        std::shared_ptr<Account> account;
        std::string const table_name = "accounts";
    public:
        AccountRepository(std::shared_ptr<Account> account);
        ~AccountRepository();
        std::vector<Account> get_all();
        void create(
            std::string name,
            std::string pin,
            std::string phone,
            std::string email,
            std::string registration_date,
            double balance
        );
        std::shared_ptr<Account> find_by_owner(std::string name);
        void update_balance(double balance_change);
        void update_pin(std::string pin);
        void update_personal_details(
            std::string owner,
            std::string phone,
            std::string email
        );
        void update(
            int id,
            std::string owner,
            std::string pin,
            std::string phone,
            std::string email
        );
        void destroy(int id);
};
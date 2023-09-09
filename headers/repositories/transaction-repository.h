#pragma once
#include <sqlite3.h>
#include <vector>
#include "./repository.h"
#include "../models/transaction-model.h"

class TransactionRepository: Repository {
    private:
        void prepare_query(std::string query);
        std::string const table_name = "transactions";
    public:
        TransactionRepository();
        ~TransactionRepository();
        void create(Transaction transaction);
        std::vector<Transaction> find_by_account_id(int account_id);
};
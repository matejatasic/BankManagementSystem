#include <iostream>
#include "account-repository.h"
#include "../errors/errors.h"

using namespace std;

 AccountRepository::AccountRepository(shared_ptr<Account> account) {
    int conn = sqlite3_open("bank-management-system.db", &this->db);

    if(conn != SQLITE_OK) {
        throw DatabaseOpenException();
    }

    if(!table_exists()) {
        throw TableDoesNotExistException();
    }

    this->account = account;
}

bool AccountRepository::table_exists() {
    const char* query = "SELECT name FROM sqlite_master WHERE type='table' AND name=?";

    this->result = sqlite3_prepare(this->db, query, -1, &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    sqlite3_bind_text(this->stmt, 1, this->table_name.c_str(), -1, SQLITE_TRANSIENT);

    this->result = sqlite3_step(this->stmt);
    bool is_table_exists = this->result == SQLITE_ROW;
    bool is_returned_result = this->result == SQLITE_DONE;

    if(!is_table_exists) {
        sqlite3_finalize(this->stmt);
        return false;
    }
    // returned result but table does not exist
    else if(is_returned_result) {
        sqlite3_finalize(this->stmt);
        throw exception();
    }

    sqlite3_finalize(this->stmt);

    return true;
}

AccountRepository::~AccountRepository() {
    sqlite3_close(this->db);
}

vector<Account> AccountRepository::get_all() {
    const string query = "SELECT * FROM " + this->table_name;

    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    vector<Account> accounts;

    while(sqlite3_step(this->stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(this->stmt, 0);
        const unsigned char* name_char = sqlite3_column_text(this->stmt, 1);
        const unsigned char* pin_char = sqlite3_column_text(this->stmt, 2);
        const unsigned char* phone_char = sqlite3_column_text(this->stmt, 3);
        const unsigned char* email_char = sqlite3_column_text(this->stmt, 4);
        const unsigned char* registration_date_char = sqlite3_column_text(this->stmt, 5);
        double balance = sqlite3_column_double(this->stmt, 6);

        string name_str(reinterpret_cast< char const* >(name_char));
        string pin(reinterpret_cast< char const* >(pin_char));
        string phone(reinterpret_cast< char const* >(phone_char));
        string email(reinterpret_cast< char const* >(email_char));
        string registration_date(reinterpret_cast< char const* >(registration_date_char));

        Account current_account;
        current_account.Init(id, name_str, pin, phone, email, registration_date, balance);
        accounts.push_back(current_account);
    }

    sqlite3_finalize(this->stmt);

    return accounts;
}

void AccountRepository::create(
    string name,
    string pin,
    string phone,
    string email,
    string registration_date,
    double balance
) {
    const string query = "INSERT INTO accounts (owner, pin, phone, email, registration_date, balance) VALUES (?, ?, ?, ?, ?, ?)";
    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    sqlite3_bind_text(this->stmt, 1, name.c_str(), name.length(), NULL);
    sqlite3_bind_text(this->stmt, 2, pin.c_str(), pin.length(), NULL);
    sqlite3_bind_text(this->stmt, 3, phone.c_str(), phone.length(), NULL);
    sqlite3_bind_text(this->stmt, 4, email.c_str(), email.length(), NULL);
    sqlite3_bind_text(this->stmt, 5, registration_date.c_str(), registration_date.length(), NULL);
    sqlite3_bind_double(this->stmt, 6, balance);

    this->result = sqlite3_step(this->stmt);
    sqlite3_finalize(this->stmt);

    if (this->result != SQLITE_DONE) {
        throw CreateException();
    }

}

shared_ptr<Account> AccountRepository::find_by_owner(string name) {
    const string query = "SELECT id, owner, pin, phone, email, registration_date, balance  FROM " + this->table_name + " WHERE owner=?";
    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    sqlite3_bind_text(this->stmt, 1, name.c_str(), name.length(), NULL);

    this->result = sqlite3_step(this->stmt);

    if (this->result == SQLITE_DONE) {
        sqlite3_finalize(this->stmt);
        throw RecordNotFound();
    }

    const unsigned char* name_char = sqlite3_column_text(this->stmt, 1);
    const unsigned char* pin_char = sqlite3_column_text(this->stmt, 2);
    const unsigned char* phone_char = sqlite3_column_text(this->stmt, 3);
    const unsigned char* email_char = sqlite3_column_text(this->stmt, 4);
    const unsigned char* registration_date_char = sqlite3_column_text(this->stmt, 5);

    int id = sqlite3_column_int(this->stmt, 0);
    string name_str(reinterpret_cast< char const* >(name_char));
    string pin(reinterpret_cast< char const* >(pin_char));
    string phone(reinterpret_cast< char const* >(phone_char));
    string email(reinterpret_cast< char const* >(email_char));
    string registration_date(reinterpret_cast< char const* >(registration_date_char));
    double balance = sqlite3_column_double(this->stmt, 6);

    this->account->Init(id, name_str, pin, phone, email, registration_date, balance);

    sqlite3_finalize(this->stmt);

    return this->account;
}

void AccountRepository::update_balance(double balance_change) {
    string operation = balance_change < 0 ? "" : "+";
    string balance_change_str = operation + " " + to_string(balance_change);
    const string query = "UPDATE " + this->table_name +" SET balance = balance " + balance_change_str + " WHERE id=?";

    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    sqlite3_bind_int(this->stmt, 1, this->account->get_id());

    this->result = sqlite3_step(this->stmt);
    sqlite3_finalize(this->stmt);

    if (this->result != SQLITE_DONE) {
        throw UpdateException();
    }
}

void AccountRepository::update_pin(string pin) {
    const string query = "UPDATE " + this->table_name +" SET pin=? WHERE id=?";

    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    sqlite3_bind_text(this->stmt, 1, pin.c_str(), pin.length(), NULL);
    sqlite3_bind_int(this->stmt, 2, this->account->get_id());

    this->result = sqlite3_step(this->stmt);
    sqlite3_finalize(this->stmt);

    if (this->result != SQLITE_DONE) {
        throw UpdateException();
    }
}

void AccountRepository::update_personal_details(
    string owner,
    string phone,
    string email
) {
    const string query = "UPDATE " + this->table_name +" SET owner=?, phone=?, email=? WHERE id=?";

    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    sqlite3_bind_text(this->stmt, 1, owner.c_str(), owner.length(), NULL);
    sqlite3_bind_text(this->stmt, 2, phone.c_str(), phone.length(), NULL);
    sqlite3_bind_text(this->stmt, 3, email.c_str(), email.length(), NULL);
    sqlite3_bind_int(this->stmt, 4, this->account->get_id());

    this->result = sqlite3_step(this->stmt);
    sqlite3_finalize(this->stmt);

    if (this->result != SQLITE_DONE) {
        throw UpdateException();
    }
}

void AccountRepository::update(
    int id,
    string owner,
    string pin,
    string phone,
    string email
) {
    const string query = "UPDATE " + this->table_name +" SET owner=?, pin=?, phone=?, email=? WHERE id=?";

    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    sqlite3_bind_text(this->stmt, 1, owner.c_str(), owner.length(), NULL);
    sqlite3_bind_text(this->stmt, 2, pin.c_str(), pin.length(), NULL);
    sqlite3_bind_text(this->stmt, 3, phone.c_str(), phone.length(), NULL);
    sqlite3_bind_text(this->stmt, 4, email.c_str(), email.length(), NULL);
    sqlite3_bind_int(this->stmt, 5, id);

    this->result = sqlite3_step(this->stmt);
    sqlite3_finalize(this->stmt);

    if (this->result != SQLITE_DONE) {
        throw UpdateException();
    }
}
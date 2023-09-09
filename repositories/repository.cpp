#include "../headers/repositories/repository.h"

bool Repository::table_exists(std::string table_name) {
    this->prepare_query("SELECT name FROM sqlite_master WHERE type='table' AND name=?");

    sqlite3_bind_text(this->stmt, 1, table_name.c_str(), -1, SQLITE_TRANSIENT);

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
        throw std::exception();
    }

    sqlite3_finalize(this->stmt);

    return true;
}

void Repository::prepare_query(std::string query) {
    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw std::exception();
    }
}
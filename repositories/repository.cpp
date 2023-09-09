#include "../headers/repositories/repository.h"

void Repository::prepare_query(std::string query) {
    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw std::exception();
    }
}
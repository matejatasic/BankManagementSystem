#include <iostream>

#include "employee-repository.h"
#include "../errors/errors.h"

using namespace std;

 EmployeeRepository::EmployeeRepository(shared_ptr<Employee> employee) {
    int conn = sqlite3_open("bank-management-system.db", &this->db);

    if(conn != SQLITE_OK) {
        throw DatabaseOpenException();
    }

    if(!table_exists()) {
        throw TableDoesNotExistException();
    }

    this->employee = employee;
}

bool EmployeeRepository::table_exists() {
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

EmployeeRepository::~EmployeeRepository() {
    sqlite3_close(this->db);
}

vector<Employee> EmployeeRepository::get_all() {
    const string query = "SELECT * FROM " + this->table_name;

    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    vector<Employee> employees;

    while(sqlite3_step(this->stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(this->stmt, 0);
        const unsigned char* username_char = sqlite3_column_text(this->stmt, 1);
        const unsigned char* password_char = sqlite3_column_text(this->stmt, 2);
        const unsigned char* phone_char = sqlite3_column_text(this->stmt, 3);
        const unsigned char* position_char = sqlite3_column_text(this->stmt, 4);

        string username(reinterpret_cast< char const* >(username_char));
        string password(reinterpret_cast< char const* >(password_char));
        string phone(reinterpret_cast< char const* >(phone_char));
        string position(reinterpret_cast< char const* >(position_char));

        Employee current_employee;
        current_employee.Init(id, username, password, phone, position);
        employees.push_back(current_employee);
    }

    sqlite3_finalize(this->stmt);

    return employees;
}

shared_ptr<Employee> EmployeeRepository::find_by_username(string username) {
    const string query = "SELECT id, username, password, phone, position FROM " + this->table_name + " WHERE username=?";
    this->result = sqlite3_prepare(this->db, query.c_str(), query.length(), &this->stmt, NULL);

    if (this->result != SQLITE_OK) {
        throw exception();
    }

    sqlite3_bind_text(this->stmt, 1, username.c_str(), username.length(), NULL);

    this->result = sqlite3_step(this->stmt);

    if (this->result == SQLITE_DONE) {
        sqlite3_finalize(this->stmt);
        throw RecordNotFound();
    }

    const unsigned char* name_char = sqlite3_column_text(this->stmt, 1);
    const unsigned char* password_char = sqlite3_column_text(this->stmt, 2);
    const unsigned char* phone_char = sqlite3_column_text(this->stmt, 3);
    const unsigned char* position_char = sqlite3_column_text(this->stmt, 4);

    int id = sqlite3_column_int(this->stmt, 0);
    string name_str(reinterpret_cast< char const* >(name_char));
    string password(reinterpret_cast< char const* >(password_char));
    string phone(reinterpret_cast< char const* >(phone_char));
    string position(reinterpret_cast< char const* >(position_char));

    this->employee->Init(id, name_str, password, phone, position);

    sqlite3_finalize(this->stmt);

    return this->employee;
}
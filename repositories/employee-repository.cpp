#include <iostream>

#include "../headers/repositories/employee-repository.h"
#include "../headers/errors/errors.h"

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
    this->prepare_query("SELECT name FROM sqlite_master WHERE type='table' AND name=?");

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
    this->prepare_query("SELECT * FROM " + this->table_name);

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

void EmployeeRepository::create(
    string username,
    string password,
    string phone,
    string position
) {
    this->prepare_query(
        "INSERT INTO " + this->table_name + " (username, password, phone, position) VALUES (?, ?, ?, ?)"
    );

    sqlite3_bind_text(this->stmt, 1, username.c_str(), username.length(), NULL);
    sqlite3_bind_text(this->stmt, 2, password.c_str(), password.length(), NULL);
    sqlite3_bind_text(this->stmt, 3, phone.c_str(), phone.length(), NULL);
    sqlite3_bind_text(this->stmt, 4, position.c_str(), position.length(), NULL);

    this->result = sqlite3_step(this->stmt);
    sqlite3_finalize(this->stmt);

    if (this->result != SQLITE_DONE) {
        throw CreateException();
    }
}

void EmployeeRepository::update(
    int id,
    string username,
    string password,
    string phone,
    string position
) {
    this->prepare_query(
        "UPDATE " + this->table_name + " SET username=?, password=?, phone=?, position=? WHERE id=?"
    );

    sqlite3_bind_text(this->stmt, 1, username.c_str(), username.length(), NULL);
    sqlite3_bind_text(this->stmt, 2, password.c_str(), password.length(), NULL);
    sqlite3_bind_text(this->stmt, 3, phone.c_str(), phone.length(), NULL);
    sqlite3_bind_text(this->stmt, 4, position.c_str(), position.length(), NULL);
    sqlite3_bind_int(this->stmt, 5, id);

    this->result = sqlite3_step(this->stmt);
    sqlite3_finalize(this->stmt);

    if (this->result != SQLITE_DONE) {
        throw UpdateException();
    }
}

void EmployeeRepository::destroy(int id) {
    this->prepare_query("DELETE FROM " + this->table_name + " WHERE id=?");

    sqlite3_bind_int(this->stmt, 1, id);

    this->result = sqlite3_step(this->stmt);
    sqlite3_finalize(this->stmt);

    if (this->result != SQLITE_DONE) {
        throw DeleteException();
    }
}

shared_ptr<Employee> EmployeeRepository::find_by_username(string username) {
    this->prepare_query(
        "SELECT * FROM " + this->table_name + " WHERE username=?"
    );

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

void EmployeeRepository::prepare_query(string query) {
    Repository::prepare_query(query);
}
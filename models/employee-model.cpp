#include "./employee-model.h"

using namespace std;

Employee::Employee() {};

void Employee::Init(
    int id,
    string username,
    string password,
    string phone,
    string position
) {
    this->id = id;
    this->username = username;
    this->password = password;
    this->phone = phone;
    this->position = position;
};

int Employee::get_id() {
    return this->id;
}

string Employee::get_username() {
    return this->username;
}

string Employee::get_password() {
    return this->password;
}

string Employee::get_phone() {
    return this->phone;
}

string Employee::get_position() {
    return this->position;
}

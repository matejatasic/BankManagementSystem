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

string Employee::get_password() {
    return this->password;
}

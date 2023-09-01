#include <iostream>
#include "customer-login-controller.h"

using namespace std;

CustomerLoginController::CustomerLoginController(
    shared_ptr<CustomerLoginService> customer_login_service,
    shared_ptr<HashService> hash_service
) {
    this->customer_login_service = customer_login_service;
    this->hash_service = hash_service;
}

void CustomerLoginController::login() {
    string name;
    string password;

    cout << "Type in your name: ";
    cin >> name;
    cout << "Type in your password: ";
    cin >> password;
    cout << "\n";

    string hashed_password = to_string(hash_service->hash(password));

    this->customer_login_service->login(name, hashed_password);

    this->error_message = this->customer_login_service->get_error_message();
}


#include <iostream>
#include "../headers/controllers/admin-login-controller.h"

using namespace std;

AdminLoginController::AdminLoginController(
    shared_ptr<AdminLoginService> admin_login_service,
    shared_ptr<HashService> hash_service
) {
    this->admin_login_service = admin_login_service;
    this->hash_service = hash_service;
}

void AdminLoginController::login() {
    string username;
    string password;

    cout << "Type in your username: ";
    cin >> username;
    cout << "Type in your password: ";
    cin >> password;
    cout << "\n";

    string hashed_password = to_string(hash_service->hash(password));

    this->admin_login_service->login(username, hashed_password);

    this->error_message = this->admin_login_service->get_error_message();
}
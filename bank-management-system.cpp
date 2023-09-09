#include <iostream>
#include <string>
#include <memory>
#include "./headers/factories/abstract-controller-factory.h"
#include "./headers/factories/admin-controller-factory.h"
#include "./headers/factories/customer-controller-factory.h"
#include "./headers/services/hash-service.h"

using namespace std;

int get_mode();
shared_ptr<AbstractControllerFactory> get_factory(int choice);

const int CUSTOMER_MODE_CHOICE = 1;
const int ADMIN_MODE_CHOICE = 2;

int main()
{
    cout << "\n\n----------------------\n";
    cout << "BANK MANAGEMENT SYSTEM";
    cout << "\n----------------------\n\n";

    int mode = get_mode();

    shared_ptr<HashService> hash_service = make_shared<HashService>();

    if (mode != CUSTOMER_MODE_CHOICE && mode != ADMIN_MODE_CHOICE) {
        cout << "Invalid mode" << endl;

        return 1;
    }

    shared_ptr<AbstractControllerFactory> controller_factory = get_factory(mode);
    shared_ptr<LoginController> login_controller = controller_factory->create_login_controller();
    shared_ptr<BankController> bank_controller = controller_factory->create_bank_controller();

    login_controller->login();

    if (login_controller->get_error_message().length() > 0) {
        cout << login_controller->get_error_message() << endl;

        return 1;
    }

    bank_controller->run_app();

    return 0;
}

int get_mode() {
    int choice;

    cout << CUSTOMER_MODE_CHOICE << ": Customer mode" << endl;
    cout << ADMIN_MODE_CHOICE << ": Admin mode" << endl;
    cout << "\n";

    cout << "Choose mode: " ;
    cin >> choice;
    cout << "\n";

    return choice;
}

shared_ptr<AbstractControllerFactory> get_factory(int choice) {
    if (choice == ADMIN_MODE_CHOICE) {
        shared_ptr<AdminControllerFactory> admin_controller_factory = make_shared<AdminControllerFactory>();

        return admin_controller_factory;
    }

    shared_ptr<CustomerControllerFactory> customer_controller_factory = make_shared<CustomerControllerFactory>();

    return customer_controller_factory;
}

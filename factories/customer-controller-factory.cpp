#include "../headers/factories/customer-controller-factory.h"
#include "../headers/repositories/account-repository.h"
#include "../headers/repositories/transaction-repository.h"
#include "../headers/services/customer-login-service.h"
#include "../headers/services/customer-service.h"
#include "../headers/services/hash-service.h"
#include "../headers/controllers/customer-login-controller.h"
#include "../headers/controllers/customer-controller.h"

using namespace std;

CustomerControllerFactory::CustomerControllerFactory() {
    // these classes are instantiated here so the
    // account information can be shared and changed accross multiple
    // classes
    this->account = make_shared<Account>();
    this->account_repository = make_shared<AccountRepository>(this->account);
}

shared_ptr<LoginController> CustomerControllerFactory::create_login_controller() {
    shared_ptr<CustomerLoginService> customer_login_service = make_shared<CustomerLoginService>(this->account_repository);
    shared_ptr<HashService> hash_service = make_shared<HashService>();
    shared_ptr<CustomerLoginController> customer_login_controller = make_shared<CustomerLoginController>(
        customer_login_service,
        hash_service
    );

    return customer_login_controller;
}

shared_ptr<BankController> CustomerControllerFactory::create_bank_controller() {
    shared_ptr<CustomerLoginService> customer_login_service = make_shared<CustomerLoginService>(this->account_repository);
    shared_ptr<TransactionRepository> transaction_repository = make_shared<TransactionRepository>();
    shared_ptr<Transaction> transaction = make_shared<Transaction>();
    shared_ptr<HashService> hash_service = make_shared<HashService>();
    shared_ptr<CustomerService> customer_service = make_shared<CustomerService>(
        this->account_repository,
        transaction_repository,
        account,
        transaction,
        hash_service
    );

    shared_ptr<CustomerController> customer_controller = make_shared<CustomerController>(customer_service);

    return customer_controller;
}
#include "../headers/factories/admin-controller-factory.h"
#include "../headers/repositories/employee-repository.h"
#include "../headers/repositories/account-repository.h"
#include "../headers/repositories/transaction-repository.h"
#include "../headers/services/admin-login-service.h"
#include "../headers/services/admin-service.h"
#include "../headers/services/hash-service.h"
#include "../headers/controllers/admin-login-controller.h"
#include "../headers/controllers/admin-controller.h"

using namespace std;

AdminControllerFactory::AdminControllerFactory() {}

shared_ptr<LoginController> AdminControllerFactory::create_login_controller() {
    shared_ptr<Employee> employee = make_shared<Employee>();
    shared_ptr<EmployeeRepository> employee_repository = make_shared<EmployeeRepository>(employee);
    shared_ptr<AdminLoginService> admin_login_service = make_shared<AdminLoginService>(employee_repository);
    shared_ptr<HashService> hash_service = make_shared<HashService>();

    shared_ptr<AdminLoginController> admin_login_controller = make_shared<AdminLoginController>(admin_login_service, hash_service);

    return admin_login_controller;
}

shared_ptr<BankController> AdminControllerFactory::create_bank_controller() {
    shared_ptr<Employee> employee = make_shared<Employee>();
    shared_ptr<EmployeeRepository> employee_repository = make_shared<EmployeeRepository>(employee);
    shared_ptr<Account> account = make_shared<Account>();
    shared_ptr<AccountRepository> account_repository = make_shared<AccountRepository>(account);
    shared_ptr<TransactionRepository> transaction_repository = make_shared<TransactionRepository>();
    shared_ptr<HashService> hash_service = make_shared<HashService>();
    shared_ptr<AdminService> admin_service = make_shared<AdminService>(
        employee_repository,
        employee,
        account_repository,
        account,
        transaction_repository,
        hash_service
    );

    shared_ptr<AdminController> admin_controller = make_shared<AdminController>(admin_service);

    return admin_controller;
}
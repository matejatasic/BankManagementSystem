#include "./admin-service.h"

using namespace std;

AdminService::AdminService(
    shared_ptr<EmployeeRepository> employee_repository,
    shared_ptr<Employee> employee,
    shared_ptr<AccountRepository> account_repository,
    shared_ptr<Account> account,
    shared_ptr<HashService> hash_service
) {};
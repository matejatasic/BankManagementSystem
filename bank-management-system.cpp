#include <iostream>
#include <string>
#include <memory>
#include "repositories/transaction-repository.h"
#include "services/validation-service.h"
#include "services/bank-service.h"
#include "services/hash-service.h"

using namespace std;

int main()
{
    string name;
    string pin;

    cout << "\n\n----------------------\n";
    cout << "BANK MANAGEMENT SYSTEM";
    cout << "\n----------------------\n\n";

    cout << "Type in your name: ";
    cin >> name;
    cout << "Type in your pin: ";
    cin >> pin;
    cout << "\n";

    shared_ptr<HashService> hash_service = make_shared<HashService>();
    string hashed_pin = to_string(hash_service->hash(pin));

    shared_ptr<Account> account = make_shared<Account>();
    shared_ptr<AccountRepository> account_repository = make_shared<AccountRepository>(account);

    ValidationService validation_service(account_repository);
    validation_service.validate_credentials(name, hashed_pin);

    if (validation_service.get_error_message().length() > 0) {
        cout << validation_service.get_error_message() << endl;

        return 1;
    }

    shared_ptr<TransactionRepository> transaction_repository = make_shared<TransactionRepository>();
    account = validation_service.get_account();
    shared_ptr<Transaction> transaction = make_shared<Transaction>();

    BankService bank_service(account_repository, transaction_repository, account, transaction, hash_service);
    bank_service.run_app();

    return 0;
}

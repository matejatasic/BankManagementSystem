#include <memory>
#include "../factories/abstract-controller-factory.h"
#include "../controllers/login-controller.h"
#include "../controllers/bank-controller.h"
#include "../models/account-model.h"
#include "../repositories/account-repository.h"

class CustomerControllerFactory: public AbstractControllerFactory {
    private:
        std::shared_ptr<Account> account;
        std::shared_ptr<AccountRepository> account_repository;
    public:
        CustomerControllerFactory();
        std::shared_ptr<LoginController> create_login_controller();
        std::shared_ptr<BankController> create_bank_controller();
};
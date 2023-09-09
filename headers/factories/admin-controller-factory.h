#include <memory>
#include "../factories/abstract-controller-factory.h"
#include "../controllers/login-controller.h"
#include "../controllers/bank-controller.h"

class AdminControllerFactory: public AbstractControllerFactory {
    public:
        AdminControllerFactory();
        std::shared_ptr<LoginController> create_login_controller();
        std::shared_ptr<BankController> create_bank_controller();
};
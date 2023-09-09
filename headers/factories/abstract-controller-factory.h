#pragma once
#include <memory>
#include "../controllers/login-controller.h"
#include "../controllers/bank-controller.h"

class AbstractControllerFactory {
    public:
        virtual std::shared_ptr<LoginController> create_login_controller() = 0;
        virtual std::shared_ptr<BankController> create_bank_controller() = 0;
};
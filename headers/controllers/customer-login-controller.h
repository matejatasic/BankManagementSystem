#include <memory>
#include "../services/customer-login-service.h"
#include "../services/hash-service.h"
#include "login-controller.h"

class CustomerLoginController: public LoginController {
    private:
        std::shared_ptr<CustomerLoginService> customer_login_service;
        std::shared_ptr<HashService> hash_service;
    public:
        CustomerLoginController(
            std::shared_ptr<CustomerLoginService> customer_login_service,
            std::shared_ptr<HashService> hash_service
        );
        void login();
        std::string get_error_message();
};
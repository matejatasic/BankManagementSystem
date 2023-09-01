#include <memory>
#include "../services/admin-login-service.h"
#include "../services/hash-service.h"
#include "login-controller.h"

class AdminLoginController: public LoginController {
    private:
        std::shared_ptr<AdminLoginService> admin_login_service;
        std::shared_ptr<HashService> hash_service;
    public:
        AdminLoginController(
            std::shared_ptr<AdminLoginService> admin_login_service,
            std::shared_ptr<HashService> hash_service
        );
        void login();
        std::string get_error_message();
};
#include "../services/admin-service.h"
#include "bank-controller.h"

class AdminController: public BankController {
    private:
        std::shared_ptr<AdminService> admin_service;

        void show_menu();
        void show_press_any_key();
    public:
        void run_app();
        AdminController(
            std::shared_ptr<AdminService> admin_service
        );
};
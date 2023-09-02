#include "../services/admin-service.h"
#include "bank-controller.h"

class AdminController: public BankController {
    static const int CHOICE_ALL_ACCOUNTS = 1;
    static const int CHOICE_FIND_ACCOUNT = 2;
    static const int CHOICE_CREATE_ACCOUNT = 3;
    static const int CHOICE_UPDATE_ACCOUNT = 4;
    static const int CHOICE_DELETE_ACCOUNT = 5;
    static const int CHOICE_VIEW_TRANSACTIONS = 6;
    static const int CHOICE_EXIT = 7;

    private:
        std::shared_ptr<AdminService> admin_service;

        void show_menu();
        void show_press_enter();
    public:
        void run_app();
        AdminController(
            std::shared_ptr<AdminService> admin_service
        );
        void see_all_accounts();
};
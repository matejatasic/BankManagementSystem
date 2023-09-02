#include "../services/admin-service.h"
#include "bank-controller.h"

class AdminController: public BankController {
    static const int CHOICE_ALL_ACCOUNTS = 1;
    static const int CHOICE_ALL_EMPLOYEES = 2;
    static const int CHOICE_SHOW_ACCOUNT = 3;
    static const int CHOICE_SHOW_EMPLOYEE = 4;
    static const int CHOICE_CREATE_ACCOUNT = 5;
    static const int CHOICE_UPDATE_ACCOUNT = 6;
    static const int CHOICE_DELETE_ACCOUNT = 7;
    static const int CHOICE_VIEW_TRANSACTIONS = 8;
    static const int CHOICE_EXIT = 9;

    private:
        std::shared_ptr<AdminService> admin_service;

        void show_menu();
        void show_press_enter();
    public:
        void run_app();
        AdminController(
            std::shared_ptr<AdminService> admin_service
        );
        void show_all_accounts();
        void show_all_employees();
        void show_account_details();
        void show_employee_details();
};
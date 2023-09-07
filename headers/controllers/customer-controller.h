#include "../services/customer-service.h"
#include "bank-controller.h"

class CustomerController: public BankController {
    static const int CHOICE_ACCOUNT_DETAILS = 1;
    static const int CHOICE_DEPOSIT = 2;
    static const int CHOICE_WITHDRAW = 3;
    static const int CHOICE_TRANSACTION = 4;
    static const int CHOICE_CHANGE_PIN = 5;
    static const int CHOICE_CHANGE_PERSONAL_DETAILS = 6;
    static const int CHOICE_EXIT = 7;

    static const std::string TEXT_ACCOUNT_DETAILS;
    static const std::string TEXT_DEPOSIT;
    static const std::string TEXT_WITHDRAW;
    static const std::string TEXT_TRANSACTION;
    static const std::string TEXT_CHANGE_PIN;
    static const std::string TEXT_CHANGE_PERSONAL_DETAILS;
    static const std::string TEXT_EXIT;

    private:
        std::shared_ptr<CustomerService> customer_service;

        void show_menu();
        void show_account_details();
        void deposit_money();
        void withdraw_money();
        void show_transaction_details();
        void change_pin();
        void change_personal_details();
        void show_press_enter();
    public:
        void run_app();
        CustomerController(
            std::shared_ptr<CustomerService> customer_service
        );
};
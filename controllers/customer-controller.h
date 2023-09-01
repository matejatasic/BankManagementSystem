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

    private:
        std::shared_ptr<CustomerService> customer_service;

        void show_menu();
        void show_account_details();
        void deposit_money();
        void withdraw_money();
        void show_transaction_details();
        void change_pin();
        void change_personal_details();
        void show_press_any_key();
    public:
        void run_app();
        CustomerController(
            std::shared_ptr<CustomerService> customer_service
        );
};
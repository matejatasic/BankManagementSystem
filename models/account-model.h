#include <string>

class Account {
    private:
        int id;
        std::string owner;
        std::string pin;
        std::string phone;
        std::string email;
        std::string registration_date;
        double balance;
    public:
        Account();
        void Init(
            int id,
            std::string owner,
            std::string pin,
            std::string phone,
            std::string email,
            std::string registration_date,
            double balance
        );

        int get_id();
        std::string get_owner();
        std::string get_pin();
        std::string get_phone();
        std::string get_email();
        std::string get_registration_date();
        double get_balance();

        Account* set_owner(std::string owner);
        Account* set_pin(std::string pin);
        Account* set_phone(std::string phone);
        Account* set_email(std::string email);
        Account* set_balance(double balance);
};
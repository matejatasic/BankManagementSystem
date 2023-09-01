#pragma once
#include <string>

class Employee {
    private:
        int id;
        std::string username;
        std::string password;
        std::string phone;
        std::string position;

    public:
        Employee();
        void Init(
            int id,
            std::string username,
            std::string password,
            std::string phone,
            std::string position
        );

        int get_id();
        std::string get_name();
        std::string get_password();
        std::string get_phone();
        std::string get_position();
};
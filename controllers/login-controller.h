#pragma once
#include <string>

class LoginController {
    protected:
        std::string error_message = "";
    public:
        virtual void login();
         std::string get_error_message();
};
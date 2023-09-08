#pragma once

class BankController {
    protected:
        void show_press_enter();
        void show_header(std::string header);
    private:
        virtual void show_menu();
    public:
        virtual void run_app();
};
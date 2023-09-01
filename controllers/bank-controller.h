#pragma once

class BankController {
    private:
        virtual void show_menu();
        virtual void show_press_any_key();
    public:
        virtual void run_app();
};
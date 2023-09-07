#pragma once

class BankController {
    protected:
        void show_press_enter();
    private:
        virtual void show_menu();
    public:
        virtual void run_app();
};
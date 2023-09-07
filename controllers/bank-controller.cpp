#include <iostream>
#include "../headers/controllers/bank-controller.h"

void BankController::run_app() {};

void BankController::show_menu() {};

void BankController::show_press_enter() {
    std::cout << "\nPress Enter to continue… ";
    std::cin.get();
    std::cin.get();
}

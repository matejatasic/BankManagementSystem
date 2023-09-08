#include <iostream>
#include "../headers/controllers/bank-controller.h"

using namespace std;

void BankController::run_app() {};

void BankController::show_menu() {};

void BankController::show_press_enter() {
    cout << "\nPress Enter to continue… ";
    cin.get();
    cin.get();
}

void BankController::show_header(string header) {
    string dashes_line = "";
    int dash_line_size = 10;

    if(header.size() > 10) {
        dash_line_size = header.size();
    }

    for (size_t i = 0; i < dash_line_size; i++) {
        dashes_line += '-';
    }

    cout << "\n" ;
    cout << header << endl;
    cout << dashes_line << endl;
    cout << "\n";
}

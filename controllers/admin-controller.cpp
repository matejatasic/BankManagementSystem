#include "./admin-controller.h"

AdminController::AdminController(std::shared_ptr<AdminService> admin_service) {
    this->admin_service = admin_service;
}

void AdminController::run_app() {};

void AdminController::show_menu() {};

void AdminController::show_press_any_key() {};

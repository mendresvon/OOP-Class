#include "Admin.h"
#include "../LibrarySystem.h"

Admin::Admin(const std::string& username, const std::string& password, int adminLevel)
    : Account(username, password), adminLevel(adminLevel) {}

int Admin::getAdminLevel() const {
    return adminLevel;
}

void Admin::setAdminLevel(int level) {
    adminLevel = level;
}

std::string Admin::getRole() const {
    return "ADMIN";
}

void Admin::showMenu(LibrarySystem& sys) {
    sys.runAdminMenu();
}

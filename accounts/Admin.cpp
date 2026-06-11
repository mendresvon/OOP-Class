#include "Admin.h"
#include "../LibrarySystem.h"
#include "../LibraryMenus.h"

Admin::Admin(const std::string& username, const std::string& passwordOrHash,
             int adminLevel, bool isHashedData, const std::string& salt)
    : Account(username, passwordOrHash, isHashedData, salt), adminLevel(adminLevel) {}

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
    LibraryMenus::runAdminMenu(sys);
}

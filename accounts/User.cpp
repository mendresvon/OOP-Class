#include "User.h"
#include "../LibrarySystem.h"
#include <algorithm>

User::User(const std::string& username, const std::string& password)
    : Account(username, password) {}

const std::vector<std::string>& User::getBorrowedIds() const {
    return borrowedIds;
}

void User::addBorrowedId(const std::string& id) {
    if (std::find(borrowedIds.begin(), borrowedIds.end(), id) == borrowedIds.end()) {
        borrowedIds.push_back(id);
    }
}

bool User::removeBorrowedId(const std::string& id) {
    auto it = std::find(borrowedIds.begin(), borrowedIds.end(), id);
    if (it != borrowedIds.end()) {
        borrowedIds.erase(it);
        return true;
    }
    return false;
}

void User::clearBorrowedIds() {
    borrowedIds.clear();
}

std::string User::getRole() const {
    return "USER";
}

void User::showMenu(LibrarySystem& sys) {
    sys.runUserMenu();
}

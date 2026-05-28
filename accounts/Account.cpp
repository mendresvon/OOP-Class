#include "Account.h"

Account::Account(const std::string& username, const std::string& password)
    : username(username), password(password) {}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getPassword() const {
    return password;
}

bool Account::checkPassword(const std::string& pwd) const {
    return password == pwd;
}


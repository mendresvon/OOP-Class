#include "LibraryService.h"

#include "accounts/Account.h"

namespace {
std::string trimCopy(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}
}

namespace LibraryService {

std::shared_ptr<Account> authenticate(
    const std::vector<std::shared_ptr<Account>>& accounts,
    const std::string& username,
    const std::string& password) {
    for (const auto& acc : accounts) {
        if (acc->getUsername() == username && acc->checkPassword(password)) {
            return acc;
        }
    }
    return nullptr;
}

bool canRegister(
    const std::vector<std::shared_ptr<Account>>& accounts,
    const std::string& username,
    const std::string& password) {
    if (trimCopy(username).empty() || trimCopy(password).empty()) {
        return false;
    }

    for (const auto& acc : accounts) {
        if (acc->getUsername() == username) {
            return false;
        }
    }
    return true;
}

}
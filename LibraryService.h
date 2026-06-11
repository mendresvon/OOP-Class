#ifndef LIBRARY_SERVICE_H
#define LIBRARY_SERVICE_H

#include <memory>
#include <string>
#include <vector>

class Account;

namespace LibraryService {
std::shared_ptr<Account> authenticate(
    const std::vector<std::shared_ptr<Account>>& accounts,
    const std::string& username,
    const std::string& password);

bool canRegister(
    const std::vector<std::shared_ptr<Account>>& accounts,
    const std::string& username,
    const std::string& password);
}

#endif
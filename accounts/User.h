#ifndef USER_H
#define USER_H

#include "Account.h"
#include <vector>

class User : public Account {
private:
    std::vector<std::string> borrowedIds;

public:
    User(const std::string& username, const std::string& passwordOrHash,
         bool isHashedData = false, const std::string& salt = "");

    const std::vector<std::string>& getBorrowedIds() const;
    void addBorrowedId(const std::string& id);
    bool removeBorrowedId(const std::string& id);
    void clearBorrowedIds();

    // Polymorphic overrides
    std::string getRole() const override;
    void showMenu(LibrarySystem& sys) override;
};

#endif

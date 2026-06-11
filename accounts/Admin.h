#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"

class Admin : public Account {
private:
    int adminLevel;

public:
    Admin(const std::string& username, const std::string& passwordOrHash,
          int adminLevel = 1, bool isHashedData = false, const std::string& salt = "");

    int getAdminLevel() const;
    void setAdminLevel(int level);

    // Polymorphic overrides
    std::string getRole() const override;
    void showMenu(LibrarySystem& sys) override;
};

#endif

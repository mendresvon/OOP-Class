#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <vector>
#include <memory>
#include <string>
#include "media/MediaItem.h"
#include "accounts/Account.h"
#include "RentalRecord.h"

class LibrarySystem {
private:
    std::vector<std::shared_ptr<MediaItem>> inventory;
    std::vector<std::shared_ptr<Account>> accounts;
    std::vector<RentalRecord> allRecords;
    std::shared_ptr<Account> currentUser;

    // Helper functions for parsing and utilities
    std::vector<std::string> split(const std::string& str, char delimiter) const;
    std::string trim(const std::string& str) const;
    std::string getTodayDateStr() const;
    int calculateDaysBetween(const std::string& date1, const std::string& date2) const;

public:
    LibrarySystem();
    ~LibrarySystem() = default;

    // Core workflows
    bool loadData();
    void saveData();
    void run();

    // Role menu loops (called by User/Admin polymorphism)
    void runUserMenu();
    void runAdminMenu();

    // Action Handlers
    bool processLogin(const std::string& username, const std::string& password);
    bool processRegister(const std::string& username, const std::string& password);
    void processLogout();

    // User Operations
    void showInventory() const;
    void searchInventory() const;
    void executeBorrow();
    void executeReturn();
    void showUserRentalHistory() const;

    // Admin Operations
    void adminAddMedia();
    void adminRemoveMedia();
    void adminViewAllAccounts() const;
    void adminViewAllRecords() const;
};

#endif

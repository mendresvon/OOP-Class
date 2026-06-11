#ifndef LIBRARY_SYSTEM_H
#define LIBRARY_SYSTEM_H

#include <vector>
#include <memory>
#include <string>
#include "media/MediaItem.h"
#include "accounts/Account.h"
#include "RentalRecord.h"

class LibrarySystem {
    friend class LibraryOperations;
    friend class LibraryViews;
    friend class LibraryMenus;
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
    void clearScreen() const;
    void pause() const;
    std::string getMaskedPassword() const;
    int getMenuSelection(const std::vector<std::string>& options, const std::string& title) const;




public:
    LibrarySystem();
    ~LibrarySystem() = default;

    // Core workflows
    bool loadData();
    void saveData();
    void run();

    // Action Handlers
    bool processLogin(const std::string& username, const std::string& password);
    bool processRegister(const std::string& username, const std::string& password);
    void processLogout();
};

#endif

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// Forward declaration to break circular dependency
class LibrarySystem;

class Account {
protected:
    std::string username;
    std::string password;

public:
    Account(const std::string& username, const std::string& password);
    virtual ~Account() = default;

    std::string getUsername() const;
    std::string getPassword() const;
    bool checkPassword(const std::string& pwd) const;


    // Pure virtual methods for polymorphism
    virtual std::string getRole() const = 0;
    virtual void showMenu(LibrarySystem& sys) = 0;
};

#endif

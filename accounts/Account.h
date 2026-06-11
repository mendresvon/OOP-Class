#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// Forward declaration to break circular dependency
class LibrarySystem;

class Account {
protected:
    std::string username;
    std::string passwordHash;
    std::string passwordSalt;

public:
    Account(const std::string& username, const std::string& passwordOrHash,
            bool isHashedData = false, const std::string& salt = "");
    virtual ~Account() = default;

    std::string getUsername() const;
    std::string getPasswordHash() const;
    std::string getPasswordSalt() const;
    bool checkPassword(const std::string& pwd) const;

    static std::string computePasswordHash(const std::string& plainPassword, const std::string& salt);
    static std::string generateSalt();


    // Pure virtual methods for polymorphism
    virtual std::string getRole() const = 0;
    virtual void showMenu(LibrarySystem& sys) = 0;
};

#endif

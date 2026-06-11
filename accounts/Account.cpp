#include "Account.h"
#include <cstdint>
#include <random>
#include <sstream>

namespace {
std::string fnv1aHex(const std::string& input) {
    const uint64_t kOffset = 14695981039346656037ull;
    const uint64_t kPrime = 1099511628211ull;
    uint64_t hash = kOffset;
    for (unsigned char c : input) {
        hash ^= c;
        hash *= kPrime;
    }

    std::ostringstream oss;
    oss << std::hex << hash;
    return oss.str();
}
}

Account::Account(const std::string& username, const std::string& passwordOrHash,
                 bool isHashedData, const std::string& salt)
    : username(username) {
    if (isHashedData) {
        passwordHash = passwordOrHash;
        passwordSalt = salt;
    } else {
        passwordSalt = generateSalt();
        passwordHash = computePasswordHash(passwordOrHash, passwordSalt);
    }
}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getPasswordHash() const {
    return passwordHash;
}

std::string Account::getPasswordSalt() const {
    return passwordSalt;
}

bool Account::checkPassword(const std::string& pwd) const {
    return computePasswordHash(pwd, passwordSalt) == passwordHash;
}

std::string Account::computePasswordHash(const std::string& plainPassword, const std::string& salt) {
    return fnv1aHex(salt + ":" + plainPassword);
}

std::string Account::generateSalt() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dist;

    std::ostringstream oss;
    oss << std::hex << dist(gen) << dist(gen);
    return oss.str();
}


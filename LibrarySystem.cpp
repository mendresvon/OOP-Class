#include "LibrarySystem.h"
#include "MenuRenderer.h"
#include "LibraryService.h"
#include "media/Book.h"
#include "media/Dvd.h"
#include "media/Magazine.h"
#include "accounts/User.h"
#include "accounts/Admin.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <cstdio>

namespace {
constexpr const char* kKvV1Header = "# format=kv-v1";

std::string escapeValue(const std::string& value) {
    std::string escaped;
    escaped.reserve(value.size());
    for (char ch : value) {
        switch (ch) {
            case '\\': escaped += "\\\\"; break;
            case '|': escaped += "\\|"; break;
            case '=': escaped += "\\="; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            default: escaped += ch; break;
        }
    }
    return escaped;
}

std::string unescapeValue(const std::string& value) {
    std::string result;
    result.reserve(value.size());
    bool escaped = false;
    for (char ch : value) {
        if (!escaped) {
            if (ch == '\\') {
                escaped = true;
            } else {
                result += ch;
            }
            continue;
        }

        switch (ch) {
            case '\\': result += '\\'; break;
            case '|': result += '|'; break;
            case '=': result += '='; break;
            case 'n': result += '\n'; break;
            case 'r': result += '\r'; break;
            default: result += ch; break;
        }
        escaped = false;
    }

    if (escaped) {
        result += '\\';
    }
    return result;
}

std::size_t findUnescapedChar(const std::string& text, char target) {
    bool escaped = false;
    for (std::size_t i = 0; i < text.size(); ++i) {
        char ch = text[i];
        if (escaped) {
            escaped = false;
            continue;
        }
        if (ch == '\\') {
            escaped = true;
            continue;
        }
        if (ch == target) {
            return i;
        }
    }
    return std::string::npos;
}

std::vector<std::string> splitByUnescapedChar(const std::string& text, char delimiter) {
    std::vector<std::string> tokens;
    std::string current;
    bool escaped = false;
    for (char ch : text) {
        if (escaped) {
            current += '\\';
            current += ch;
            escaped = false;
            continue;
        }
        if (ch == '\\') {
            escaped = true;
            continue;
        }
        if (ch == delimiter) {
            tokens.push_back(current);
            current.clear();
            continue;
        }
        current += ch;
    }
    if (escaped) {
        current += '\\';
    }
    tokens.push_back(current);
    return tokens;
}

std::string trimCopy(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> splitByChar(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

using FieldMap = std::unordered_map<std::string, std::string>;

bool parseKvLine(const std::string& line, FieldMap& out) {
    out.clear();
    auto parts = splitByUnescapedChar(line, '|');
    for (const auto& part : parts) {
        auto eqPos = findUnescapedChar(part, '=');
        if (eqPos == std::string::npos || eqPos == 0) {
            return false;
        }
        std::string key = unescapeValue(trimCopy(part.substr(0, eqPos)));
        std::string value = unescapeValue(trimCopy(part.substr(eqPos + 1)));
        if (key.empty()) {
            return false;
        }
        out[key] = value;
    }
    return !out.empty();
}

void reportParseIssue(std::vector<std::string>& issues,
                      const std::string& filePath,
                      std::size_t lineNumber,
                      const std::string& message,
                      const std::string& rawLine) {
    std::ostringstream oss;
    oss << filePath << ':' << lineNumber << " - " << message;
    if (!rawLine.empty()) {
        oss << " | " << rawLine;
    }
    issues.push_back(oss.str());
    std::cerr << "[kv-v1] " << oss.str() << '\n';
}

bool atomicWriteTextFile(const std::string& targetPath, const std::string& content) {
    std::string tempPath = targetPath + ".tmp";
    {
        std::ofstream out(tempPath, std::ios::trunc);
        if (!out.is_open()) {
            return false;
        }
        out << content;
        if (!out.good()) {
            return false;
        }
    }

    std::remove(targetPath.c_str());
    return std::rename(tempPath.c_str(), targetPath.c_str()) == 0;
}

class PersistenceRepository {
public:
    bool load(std::vector<std::shared_ptr<MediaItem>>& inventory,
              std::vector<std::shared_ptr<Account>>& accounts,
              std::vector<RentalRecord>& allRecords) const;

    bool save(const std::vector<std::shared_ptr<MediaItem>>& inventory,
              const std::vector<std::shared_ptr<Account>>& accounts,
              const std::vector<RentalRecord>& allRecords) const;

private:
    struct ParseContext {
        std::vector<std::string> issues;
    };

    static bool validateHeader(std::ifstream& in, const std::string& filePath, ParseContext& context);
    static bool hasRequiredKeys(const FieldMap& fields,
                                const std::vector<std::string>& required,
                                const std::string& filePath,
                                std::size_t lineNumber,
                                const std::string& rawLine,
                                ParseContext& context);
    static bool writeTextFile(const std::string& targetPath, const std::string& content);
    static bool restoreFromBackup(const std::string& targetPath, const std::string& backupPath);
    static bool backupFile(const std::string& sourcePath, const std::string& backupPath);
};

bool PersistenceRepository::validateHeader(std::ifstream& in,
                                           const std::string& filePath,
                                           ParseContext& context) {
    std::string header;
    std::size_t lineNumber = 0;
    while (std::getline(in, header)) {
        ++lineNumber;
        header = trimCopy(header);
        if (header.empty()) {
            continue;
        }
        if (header == kKvV1Header) {
            return true;
        }
        reportParseIssue(context.issues, filePath, lineNumber,
                         "invalid or missing kv-v1 header", header);
        return false;
    }
    reportParseIssue(context.issues, filePath, 0, "missing kv-v1 header", std::string());
    return false;
}

bool PersistenceRepository::hasRequiredKeys(const FieldMap& fields,
                                            const std::vector<std::string>& required,
                                            const std::string& filePath,
                                            std::size_t lineNumber,
                                            const std::string& rawLine,
                                            ParseContext& context) {
    for (const auto& key : required) {
        auto it = fields.find(key);
        if (it == fields.end() || trimCopy(it->second).empty()) {
            reportParseIssue(context.issues, filePath, lineNumber,
                             "missing required key: " + key, rawLine);
            return false;
        }
    }
    return true;
}

bool PersistenceRepository::writeTextFile(const std::string& targetPath, const std::string& content) {
    return atomicWriteTextFile(targetPath, content);
}

bool PersistenceRepository::backupFile(const std::string& sourcePath, const std::string& backupPath) {
    std::ifstream in(sourcePath, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }
    std::ofstream out(backupPath, std::ios::binary | std::ios::trunc);
    if (!out.is_open()) {
        return false;
    }
    out << in.rdbuf();
    return out.good();
}

bool PersistenceRepository::restoreFromBackup(const std::string& targetPath, const std::string& backupPath) {
    std::ifstream in(backupPath, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }
    std::ofstream out(targetPath, std::ios::binary | std::ios::trunc);
    if (!out.is_open()) {
        return false;
    }
    out << in.rdbuf();
    return out.good();
}

bool PersistenceRepository::load(std::vector<std::shared_ptr<MediaItem>>& inventory,
                                 std::vector<std::shared_ptr<Account>>& accounts,
                                 std::vector<RentalRecord>& allRecords) const {
    inventory.clear();
    accounts.clear();
    allRecords.clear();

    std::ifstream invFile("data/inventory.txt");
    std::ifstream accFile("data/accounts.txt");
    std::ifstream recFile("data/rental_records.txt");
    if (!invFile.is_open() || !accFile.is_open() || !recFile.is_open()) {
        return false;
    }

    ParseContext context;
    if (!validateHeader(invFile, "data/inventory.txt", context) ||
        !validateHeader(accFile, "data/accounts.txt", context) ||
        !validateHeader(recFile, "data/rental_records.txt", context)) {
        return false;
    }

    auto getField = [](const FieldMap& fields, const std::string& key) -> std::string {
        auto it = fields.find(key);
        return it == fields.end() ? std::string() : it->second;
    };

    std::string line;
    std::size_t invLine = 1;
    while (std::getline(invFile, line)) {
        ++invLine;
        line = trimCopy(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        FieldMap fields;
        if (!parseKvLine(line, fields)) {
            reportParseIssue(context.issues, "data/inventory.txt", invLine, "invalid kv line", line);
            continue;
        }

        if (!hasRequiredKeys(fields, {"type", "id", "title", "borrowed", "status"},
                             "data/inventory.txt", invLine, line, context)) {
            continue;
        }

        std::string type = getField(fields, "type");
        std::string id = getField(fields, "id");
        std::string title = getField(fields, "title");
        bool borrowed = getField(fields, "borrowed") == "1";
        std::string status = getField(fields, "status");
        if (status.empty()) {
            status = "ACTIVE";
        }

        if (type == "BOOK") {
            if (!hasRequiredKeys(fields, {"author", "isbn"}, "data/inventory.txt", invLine, line, context)) {
                continue;
            }
            inventory.push_back(std::make_shared<Book>(
                id, title, borrowed, getField(fields, "author"), getField(fields, "isbn"), status));
        } else if (type == "DVD") {
            if (!hasRequiredKeys(fields, {"director", "duration"}, "data/inventory.txt", invLine, line, context)) {
                continue;
            }
            int duration = 0;
            try {
                duration = std::stoi(getField(fields, "duration"));
            } catch (...) {
                reportParseIssue(context.issues, "data/inventory.txt", invLine, "invalid duration", line);
                duration = 0;
            }
            inventory.push_back(std::make_shared<Dvd>(
                id, title, borrowed, getField(fields, "director"), duration, status));
        } else if (type == "MAGAZINE") {
            if (!hasRequiredKeys(fields, {"issue", "month"}, "data/inventory.txt", invLine, line, context)) {
                continue;
            }
            int issue = 0;
            int month = 0;
            try {
                issue = std::stoi(getField(fields, "issue"));
            } catch (...) {
                reportParseIssue(context.issues, "data/inventory.txt", invLine, "invalid issue", line);
                issue = 0;
            }
            try {
                month = std::stoi(getField(fields, "month"));
            } catch (...) {
                reportParseIssue(context.issues, "data/inventory.txt", invLine, "invalid month", line);
                month = 0;
            }
            inventory.push_back(std::make_shared<Magazine>(
                id, title, borrowed, issue, month, status));
        } else {
            reportParseIssue(context.issues, "data/inventory.txt", invLine, "unknown media type", line);
        }
    }

    std::size_t accLine = 1;
    while (std::getline(accFile, line)) {
        ++accLine;
        line = trimCopy(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        FieldMap fields;
        if (!parseKvLine(line, fields)) {
            reportParseIssue(context.issues, "data/accounts.txt", accLine, "invalid kv line", line);
            continue;
        }

        if (!hasRequiredKeys(fields, {"username", "role", "passwordHash", "passwordSalt"},
                             "data/accounts.txt", accLine, line, context)) {
            continue;
        }

        std::string username = getField(fields, "username");
        std::string role = getField(fields, "role");
        std::string hash = getField(fields, "passwordHash");
        std::string salt = getField(fields, "passwordSalt");
        std::string borrowedField = getField(fields, "borrowed");

        if (role == "ADMIN") {
            if (!hasRequiredKeys(fields, {"adminLevel"}, "data/accounts.txt", accLine, line, context)) {
                continue;
            }
            int adminLevel = 1;
            try {
                adminLevel = std::stoi(getField(fields, "adminLevel"));
            } catch (...) {
                reportParseIssue(context.issues, "data/accounts.txt", accLine, "invalid adminLevel", line);
                adminLevel = 1;
            }
            accounts.push_back(std::make_shared<Admin>(username, hash, adminLevel, true, salt));
        } else {
            auto user = std::make_shared<User>(username, hash, true, salt);
            if (!borrowedField.empty()) {
                for (const auto& id : splitByChar(borrowedField, ';')) {
                    if (!trimCopy(id).empty()) {
                        user->addBorrowedId(trimCopy(id));
                    }
                }
            }
            accounts.push_back(user);
        }
    }

    std::size_t recLine = 1;
    while (std::getline(recFile, line)) {
        ++recLine;
        line = trimCopy(line);
        if (line.empty() || line[0] == '#') {
            continue;
        }

        FieldMap fields;
        if (!parseKvLine(line, fields)) {
            reportParseIssue(context.issues, "data/rental_records.txt", recLine, "invalid kv line", line);
            continue;
        }

        if (!hasRequiredKeys(fields,
                             {"recordId", "username", "itemId", "itemTitle", "borrowDate", "returnDate", "rentalFee", "status"},
                             "data/rental_records.txt", recLine, line, context)) {
            continue;
        }

        RentalRecord rec;
        rec.recordId = getField(fields, "recordId");
        rec.username = getField(fields, "username");
        rec.itemId = getField(fields, "itemId");
        rec.itemTitle = getField(fields, "itemTitle");
        rec.borrowDate = getField(fields, "borrowDate");
        rec.returnDate = getField(fields, "returnDate");
        try {
            rec.rentalFee = std::stod(getField(fields, "rentalFee"));
        } catch (...) {
            reportParseIssue(context.issues, "data/rental_records.txt", recLine, "invalid rentalFee", line);
            rec.rentalFee = 0.0;
        }
        rec.status = getField(fields, "status");
        allRecords.push_back(rec);
    }

    for (const auto& acc : accounts) {
        if (acc->getRole() != "USER") {
            continue;
        }
        auto user = std::dynamic_pointer_cast<User>(acc);
        if (user == nullptr) {
            continue;
        }
        for (const auto& id : user->getBorrowedIds()) {
            for (const auto& item : inventory) {
                if (item->getId() == id) {
                    item->setBorrowed(true);
                    break;
                }
            }
        }
    }

    return true;
}

bool PersistenceRepository::save(const std::vector<std::shared_ptr<MediaItem>>& inventory,
                                 const std::vector<std::shared_ptr<Account>>& accounts,
                                 const std::vector<RentalRecord>& allRecords) const {
    std::ostringstream invOut;
    invOut << kKvV1Header << "\n";
    for (const auto& item : inventory) {
        if (auto book = std::dynamic_pointer_cast<Book>(item)) {
            invOut << "type=BOOK|id=" << escapeValue(book->getId())
                   << "|title=" << escapeValue(book->getTitle())
                   << "|borrowed=" << (book->isBorrowedItem() ? 1 : 0)
                   << "|author=" << escapeValue(book->getAuthor())
                   << "|isbn=" << escapeValue(book->getIsbn())
                   << "|status=" << escapeValue(book->getStatus()) << "\n";
        } else if (auto dvd = std::dynamic_pointer_cast<Dvd>(item)) {
            invOut << "type=DVD|id=" << escapeValue(dvd->getId())
                   << "|title=" << escapeValue(dvd->getTitle())
                   << "|borrowed=" << (dvd->isBorrowedItem() ? 1 : 0)
                   << "|director=" << escapeValue(dvd->getDirector())
                   << "|duration=" << dvd->getDuration()
                   << "|status=" << escapeValue(dvd->getStatus()) << "\n";
        } else if (auto mag = std::dynamic_pointer_cast<Magazine>(item)) {
            invOut << "type=MAGAZINE|id=" << escapeValue(mag->getId())
                   << "|title=" << escapeValue(mag->getTitle())
                   << "|borrowed=" << (mag->isBorrowedItem() ? 1 : 0)
                   << "|issue=" << mag->getIssueNum()
                   << "|month=" << mag->getMonth()
                   << "|status=" << escapeValue(mag->getStatus()) << "\n";
        }
    }

    std::ostringstream accOut;
    accOut << kKvV1Header << "\n";
    for (const auto& acc : accounts) {
        accOut << "username=" << escapeValue(acc->getUsername())
               << "|role=" << escapeValue(acc->getRole())
               << "|passwordHash=" << escapeValue(acc->getPasswordHash())
               << "|passwordSalt=" << escapeValue(acc->getPasswordSalt());
        if (acc->getRole() == "ADMIN") {
            auto admin = std::dynamic_pointer_cast<Admin>(acc);
            accOut << "|adminLevel=" << (admin != nullptr ? admin->getAdminLevel() : 1);
        } else {
            auto user = std::dynamic_pointer_cast<User>(acc);
            accOut << "|borrowed=";
            if (user != nullptr) {
                const auto& borrowed = user->getBorrowedIds();
                for (size_t i = 0; i < borrowed.size(); ++i) {
                    if (i > 0) {
                        accOut << ';';
                    }
                    accOut << escapeValue(borrowed[i]);
                }
            }
        }
        accOut << "\n";
    }

    std::ostringstream recOut;
    recOut << kKvV1Header << "\n";
    for (const auto& rec : allRecords) {
        recOut << "recordId=" << escapeValue(rec.recordId)
               << "|username=" << escapeValue(rec.username)
               << "|itemId=" << escapeValue(rec.itemId)
               << "|itemTitle=" << escapeValue(rec.itemTitle)
               << "|borrowDate=" << escapeValue(rec.borrowDate)
               << "|returnDate=" << escapeValue(rec.returnDate)
               << "|rentalFee=" << rec.rentalFee
               << "|status=" << escapeValue(rec.status) << "\n";
    }

    const std::string invPath = "data/inventory.txt";
    const std::string accPath = "data/accounts.txt";
    const std::string recPath = "data/rental_records.txt";
    const std::string invBak = invPath + ".bak";
    const std::string accBak = accPath + ".bak";
    const std::string recBak = recPath + ".bak";

    bool invBacked = backupFile(invPath, invBak);
    backupFile(accPath, accBak);
    bool recBacked = backupFile(recPath, recBak);

    bool invSaved = writeTextFile(invPath, invOut.str());
    bool accSaved = invSaved && writeTextFile(accPath, accOut.str());
    bool recSaved = accSaved && writeTextFile(recPath, recOut.str());

    if (!recSaved) {
        if (!invSaved && invBacked) {
            restoreFromBackup(invPath, invBak);
        }
        if (invSaved && !accSaved && invBacked) {
            restoreFromBackup(invPath, invBak);
        }
        if (accSaved && recBacked) {
            restoreFromBackup(accPath, accBak);
            if (invBacked) {
                restoreFromBackup(invPath, invBak);
            }
        }
        if (recBacked) {
            restoreFromBackup(recPath, recBak);
        }
    }

    std::remove(invBak.c_str());
    std::remove(accBak.c_str());
    std::remove(recBak.c_str());

    return invSaved && accSaved && recSaved;
}

} // namespace

LibrarySystem::LibrarySystem() : currentUser(nullptr) {
    MenuRenderer::initialize();
}

std::vector<std::string> LibrarySystem::split(const std::string& str, char delimiter) const {
    return splitByChar(str, delimiter);
}

std::string LibrarySystem::trim(const std::string& str) const {
    return trimCopy(str);
}

std::string LibrarySystem::getTodayDateStr() const {
    std::time_t now = std::time(nullptr);
    std::tm localTime{};
    if (std::tm* localTimePtr = std::localtime(&now)) {
        localTime = *localTimePtr;
    }
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d");
    return oss.str();
}

int LibrarySystem::calculateDaysBetween(const std::string& date1, const std::string& date2) const {
    auto parseDate = [](const std::string& date) -> std::time_t {
        std::tm tm{};
        std::istringstream iss(date);
        iss >> std::get_time(&tm, "%Y-%m-%d");
        if (iss.fail()) {
            return static_cast<std::time_t>(0);
        }
        tm.tm_isdst = -1;
        return std::mktime(&tm);
    };

    std::time_t t1 = parseDate(date1);
    std::time_t t2 = parseDate(date2);
    if (t1 == 0 || t2 == 0) {
        return 0;
    }
    double diff = std::difftime(t2, t1) / (60.0 * 60.0 * 24.0);
    return diff > 0 ? static_cast<int>(diff) : 0;
}

void LibrarySystem::clearScreen() const {
    MenuRenderer::clearScreen();
}

void LibrarySystem::pause() const {
    MenuRenderer::pause();
}

std::string LibrarySystem::getMaskedPassword() const {
    return MenuRenderer::getMaskedPassword();
}

int LibrarySystem::getMenuSelection(const std::vector<std::string>& options, const std::string& title) const {
    return MenuRenderer::getMenuSelection(options, title);
}

void LibrarySystem::processLogout() {
    currentUser = nullptr;
}

void LibrarySystem::run() {
    if (!loadData()) {
        std::cout << "\n❌ 系統啟動失敗：資料格式不符合 kv-v1 要求。\n";
        return;
    }

    while (true) {
        if (currentUser == nullptr) {
            std::vector<std::string> options = {
                "登入系統",
                "註冊帳號",
                "離開系統"
            };
            std::string title = "\n===============================================\n"
                                "     歡迎使用 智慧多媒體租借管理系統 (v1.0)     \n"
                                "===============================================\n"
                                "請選擇操作項目:";
            int selection = getMenuSelection(options, title);

            if (selection == 0) {
                std::cout << "請輸入帳號: ";
                std::string user;
                std::getline(std::cin, user);
                user = trim(user);

                std::cout << "請輸入密碼: ";
                std::string pass = getMaskedPassword();
                pass = trim(pass);

                if (processLogin(user, pass)) {
                    std::cout << "\n登入成功！歡迎回到系統。\n";
                    pause();
                } else {
                    std::cout << "\n❌ 登入失敗：帳號或密碼錯誤。\n";
                    pause();
                }
            } else if (selection == 1) {
                std::cout << "請設定新帳號: ";
                std::string user;
                std::getline(std::cin, user);
                user = trim(user);

                std::cout << "請設定新密碼: ";
                std::string pass = getMaskedPassword();
                pass = trim(pass);

                if (processRegister(user, pass)) {
                    std::cout << "\n註冊成功！您現在可以進行登入了。\n";
                } else {
                    std::cout << "\n❌ 註冊失敗：帳號已存在或輸入不合法。\n";
                }

                pause();
            } else if (selection == 2) {
                std::cout << "\n謝謝使用，再見！\n";
                break;
            }
        } else {
            currentUser->showMenu(*this);
        }
    }
}

bool LibrarySystem::loadData() {
    PersistenceRepository repository;
    if (!repository.load(inventory, accounts, allRecords)) {
        std::cout << "\n❌ 資料載入失敗：檔案缺失、標頭錯誤或內容損毀。\n";
        return false;
    }
    return true;
}

void LibrarySystem::saveData() {
    PersistenceRepository repository;
    if (!repository.save(inventory, accounts, allRecords)) {
        std::cout << "\n❌ 儲存失敗：無法寫入資料檔。\n";
    }
}

bool LibrarySystem::processLogin(const std::string& username, const std::string& password) {
    auto matched = LibraryService::authenticate(accounts, username, password);
    if (matched != nullptr) {
        currentUser = matched;
        return true;
    }
    return false;
}

bool LibrarySystem::processRegister(const std::string& username, const std::string& password) {
    if (!LibraryService::canRegister(accounts, username, password)) {
        return false;
    }

    accounts.push_back(std::make_shared<User>(username, password));
    saveData();
    return true;
}




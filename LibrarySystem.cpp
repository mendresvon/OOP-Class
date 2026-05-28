#include "LibrarySystem.h"
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

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif


LibrarySystem::LibrarySystem() : currentUser(nullptr) {}

// Helper: Split string by delimiter
std::vector<std::string> LibrarySystem::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(str);
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Helper: Trim whitespace from both ends
std::string LibrarySystem::trim(const std::string& str) const {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Helper: Get today's date in YYYY-MM-DD
std::string LibrarySystem::getTodayDateStr() const {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", now);
    return std::string(buf);
}

// Helper: Calculate days between two date strings (YYYY-MM-DD)
int LibrarySystem::calculateDaysBetween(const std::string& date1, const std::string& date2) const {
    if (date1 == "Pending" || date2 == "Pending") return 0;
    
    std::tm tm1 = {};
    std::tm tm2 = {};
    std::stringstream ss1(date1);
    std::stringstream ss2(date2);
    
    char dash;
    ss1 >> tm1.tm_year >> dash >> tm1.tm_mon >> dash >> tm1.tm_mday;
    ss2 >> tm2.tm_year >> dash >> tm2.tm_mon >> dash >> tm2.tm_mday;
    
    tm1.tm_year -= 1900;
    tm1.tm_mon -= 1;
    tm1.tm_isdst = -1;
    
    tm2.tm_year -= 1900;
    tm2.tm_mon -= 1;
    tm2.tm_isdst = -1;
    
    std::time_t t1 = std::mktime(&tm1);
    std::time_t t2 = std::mktime(&tm2);
    
    if (t1 == -1 || t2 == -1) return 0;
    
    double diff = std::difftime(t2, t1);
    int days = static_cast<int>(diff / (60 * 60 * 24));
    return days < 0 ? 0 : days;
}

void LibrarySystem::clearScreen() const {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void LibrarySystem::pause() const {
    std::cout << "\n請按 Enter 鍵繼續...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

std::string LibrarySystem::getMaskedPassword() const {
    std::string password;
    char ch;
#ifdef _WIN32
    while ((ch = _getch()) != '\r' && ch != '\n') {
        if (ch == '\b') { // Backspace
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else if (ch == 0 || (unsigned char)ch == 224) { // Ignore special keys
            _getch();
        } else if (ch >= 32 && ch <= 126) {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
#else
    // POSIX terminal masking (Linux / macOS)
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    std::getline(std::cin, password);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl;
#endif
    return password;
}

int LibrarySystem::getMenuSelection(const std::vector<std::string>& options, const std::string& title) const {
    if (options.empty()) return -1;
    int selected = 0;
    while (true) {
        clearScreen();
        std::cout << title << "\n";
        
        for (size_t i = 0; i < options.size(); ++i) {
            if (static_cast<int>(i) == selected) {
                // Highlight option with reverse video ANSI 7m
                std::cout << "\033[7m  ➔ " << options[i] << "  \033[0m\n";
            } else {
                std::cout << "     " << options[i] << "\n";
            }
        }
        std::cout << "\n===============================================\n";
        std::cout << "(提示: 請使用 ⌨️ 上下鍵 [↑][↓] 移動，按下 [Enter] 確認選擇)\n";
        
#ifdef _WIN32
        char ch = _getch();
        if ((unsigned char)ch == 224 || ch == 0) { // Special keys prefix
            char arrow = _getch();
            if (arrow == 72) {      // Up arrow
                selected = (selected - 1 + options.size()) % options.size();
            } else if (arrow == 80) { // Down arrow
                selected = (selected + 1) % options.size();
            }
        } else if (ch == 13 || ch == 10) { // Enter key
            break;
        }
#else
        // POSIX keyboard arrow key intercept fallback using standard terminal modes
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        char ch;
        int n = read(STDIN_FILENO, &ch, 1);
        if (n > 0) {
            if (ch == 27) { // Escape sequence for arrow keys
                char seq[2];
                if (read(STDIN_FILENO, &seq[0], 1) > 0 && read(STDIN_FILENO, &seq[1], 1) > 0) {
                    if (seq[0] == '[') {
                        if (seq[1] == 'A') { // Up arrow
                            selected = (selected - 1 + options.size()) % options.size();
                        } else if (seq[1] == 'B') { // Down arrow
                            selected = (selected + 1) % options.size();
                        }
                    }
                }
            } else if (ch == 10 || ch == 13) { // Enter key
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
                break;
            }
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    }
    return selected;
}




// core: Load all databases from files
bool LibrarySystem::loadData() {
    inventory.clear();
    accounts.clear();
    allRecords.clear();

    // 1. Load Inventory
    std::ifstream invFile("data/inventory.txt");
    if (invFile.is_open()) {
        std::string line;
        while (std::getline(invFile, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') continue;
            auto fields = split(line, ',');
            if (fields.size() < 4) continue;

            std::string type = fields[0];
            std::string id = fields[1];
            std::string title = fields[2];
            bool isBorrowed = (fields[3] == "1");

            std::string status = "ACTIVE";
            if (fields.size() >= 7) {
                status = fields[6];
            }

            if (type == "BOOK" && fields.size() >= 6) {
                inventory.push_back(std::make_shared<Book>(id, title, isBorrowed, fields[4], fields[5], status));
            } else if (type == "DVD" && fields.size() >= 6) {
                inventory.push_back(std::make_shared<Dvd>(id, title, isBorrowed, fields[4], std::stoi(fields[5]), status));
            } else if (type == "MAGAZINE" && fields.size() >= 6) {
                inventory.push_back(std::make_shared<Magazine>(id, title, isBorrowed, std::stoi(fields[4]), std::stoi(fields[5]), status));
            }
        }
        invFile.close();
    }


    // 2. Load Accounts
    std::ifstream accFile("data/accounts.txt");
    if (accFile.is_open()) {
        std::string line;
        while (std::getline(accFile, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') continue;
            auto fields = split(line, ',');
            if (fields.size() < 3) continue;

            std::string username = fields[0];
            std::string password = fields[1];
            std::string role = fields[2];

            if (role == "ADMIN" && fields.size() >= 4) {
                int level = std::stoi(fields[3]);
                accounts.push_back(std::make_shared<Admin>(username, password, level));
            } else if (role == "USER") {
                auto user = std::make_shared<User>(username, password);
                if (fields.size() >= 4 && !fields[3].empty()) {
                    auto borrowed = split(fields[3], ';');
                    for (const auto& item : borrowed) {
                        if (!trim(item).empty()) {
                            user->addBorrowedId(trim(item));
                        }
                    }
                }
                accounts.push_back(user);
            }
        }
        accFile.close();
    }

    // 3. Load Rental Records
    std::ifstream recFile("data/rental_records.txt");
    if (recFile.is_open()) {
        std::string line;
        while (std::getline(recFile, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') continue;
            auto fields = split(line, ',');
            if (fields.size() < 8) continue;

            RentalRecord rec;
            rec.recordId = fields[0];
            rec.username = fields[1];
            rec.itemId = fields[2];
            rec.itemTitle = fields[3];
            rec.borrowDate = fields[4];
            rec.returnDate = fields[5];
            rec.rentalFee = std::stod(fields[6]);
            rec.status = fields[7];

            allRecords.push_back(rec);
        }
        recFile.close();
    }

    return true;
}

// core: Save all databases to files
void LibrarySystem::saveData() {
    // 1. Save Inventory
    std::ofstream invFile("data/inventory.txt");
    if (invFile.is_open()) {
        for (const auto& item : inventory) {
            invFile << item->serialize() << "\n";
        }
        invFile.close();
    }

    // 2. Save Accounts
    std::ofstream accFile("data/accounts.txt");
    if (accFile.is_open()) {
        for (const auto& acc : accounts) {
            accFile << acc->getUsername() << "," << acc->getPassword() << "," << acc->getRole();
            if (acc->getRole() == "ADMIN") {
                auto admin = std::dynamic_pointer_cast<Admin>(acc);
                accFile << "," << admin->getAdminLevel() << "\n";
            } else {
                auto user = std::dynamic_pointer_cast<User>(acc);
                accFile << ",";
                const auto& borrowed = user->getBorrowedIds();
                for (size_t i = 0; i < borrowed.size(); ++i) {
                    accFile << borrowed[i];
                    if (i < borrowed.size() - 1) accFile << ";";
                }
                accFile << "\n";
            }
        }
        accFile.close();
    }

    // 3. Save Rental Records
    std::ofstream recFile("data/rental_records.txt");
    if (recFile.is_open()) {
        for (const auto& rec : allRecords) {
            recFile << rec.recordId << "," << rec.username << "," << rec.itemId << ","
                    << rec.itemTitle << "," << rec.borrowDate << "," << rec.returnDate << ","
                    << std::fixed << std::setprecision(1) << rec.rentalFee << "," << rec.status << "\n";
        }
        recFile.close();
    }
}

// core: Authentication logic
bool LibrarySystem::processLogin(const std::string& username, const std::string& password) {
    for (const auto& acc : accounts) {
        if (acc->getUsername() == username && acc->checkPassword(password)) {
            currentUser = acc;
            return true;
        }
    }
    return false;
}

bool LibrarySystem::processRegister(const std::string& username, const std::string& password) {
    for (const auto& acc : accounts) {
        if (acc->getUsername() == username) {
            return false; // Username already exists
        }
    }
    accounts.push_back(std::make_shared<User>(username, password));
    saveData();
    return true;
}

void LibrarySystem::processLogout() {
    currentUser = nullptr;
}

// core: Main Execution Loop
void LibrarySystem::run() {
    loadData();
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
                    std::cout << "\n❌ 註冊失敗：此帳號已存在。\n";
                }

                pause();
            } else if (selection == 2) {
                std::cout << "\n謝謝使用，再見！\n";
                break;
            }
        } else {
            // Polymorphic dispatch to roles
            currentUser->showMenu(*this);
        }
    }
}

// UI: User Menu Loop
void LibrarySystem::runUserMenu() {
    std::vector<std::string> options = {
        "瀏覽所有館藏 (圖書/DVD/雜誌)",
        "搜尋館藏 (按關鍵字/類型)",
        "借閱多媒體 (輸入 ID)",
        "歸還多媒體 (輸入 ID)",
        "查看我的借閱紀錄 & 應付租金",
        "登出系統"
    };
    std::string title = "\n===============================================\n"
                        "   【使用者控制台】 歡迎, " + currentUser->getUsername() + "! (一般會員)\n"
                        "===============================================\n"
                        "請選擇操作項目:";
    int selection = getMenuSelection(options, title);

    if (selection == 0) {
        showInventory();
    } else if (selection == 1) {
        searchInventory();
    } else if (selection == 2) {
        executeBorrow();
    } else if (selection == 3) {
        executeReturn();
    } else if (selection == 4) {
        showUserRentalHistory();
    } else if (selection == 5) {
        processLogout();
        std::cout << "\n已成功登出系統。\n";
        pause();
    }
}

// UI: Admin Menu Loop
void LibrarySystem::runAdminMenu() {
    std::vector<std::string> options = {
        "新增多媒體館藏 (圖書/DVD/雜誌)",
        "下架/刪除多媒體館藏",
        "查看所有使用者名單 & 借閱狀態",
        "檢視全館租借交易日誌 (Rental Log)",
        "資源回收桶與封存管理中心",
        "登出系統"
    };
    std::string title = "\n===============================================\n"
                        "      【管理者主控台】 歡迎, " + currentUser->getUsername() + "! (系統管理員)\n"
                        "===============================================\n"
                        "請選擇操作項目:";
    int selection = getMenuSelection(options, title);

    if (selection == 0) {
        adminAddMedia();
    } else if (selection == 1) {
        adminRemoveMedia();
    } else if (selection == 2) {
        adminViewAllAccounts();
    } else if (selection == 3) {
        adminViewAllRecords();
    } else if (selection == 4) {
        adminRecycleBinMenu();
    } else if (selection == 5) {
        processLogout();
        std::cout << "\n已成功登出系統。\n";
        pause();
    }
}


// User Action: Display all library inventory
void LibrarySystem::showInventory() const {
    if (inventory.empty()) {
        std::cout << "\n目前圖書館沒有任何館藏庫存。\n";
        pause();
        return;
    }
    
    // Check if there is any visible item for regular users
    bool hasVisible = false;
    for (const auto& item : inventory) {
        if (currentUser != nullptr && currentUser->getRole() == "USER" && item->getStatus() != "ACTIVE") {
            continue;
        }
        hasVisible = true;
        break;
    }
    if (!hasVisible) {
        std::cout << "\n目前圖書館沒有任何館藏庫存。\n";
        pause();
        return;
    }

    std::cout << "\n----------------------- 圖書館館藏列表 -----------------------\n";
    std::cout << std::left << std::setw(8) << "ID" << std::setw(25) << "名稱" << std::setw(10) << "類別" << std::setw(10) << "狀態" << "詳細資料\n";
    std::cout << "------------------------------------------------------------\n";
    for (const auto& item : inventory) {
        if (currentUser != nullptr && currentUser->getRole() == "USER" && item->getStatus() != "ACTIVE") {
            continue;
        }
        std::string type = "未知";
        std::string details = "";
        
        if (std::dynamic_pointer_cast<Book>(item)) {
            type = "圖書 (Book)";
            auto book = std::dynamic_pointer_cast<Book>(item);
            details = "作者: " + book->getAuthor() + " | ISBN: " + book->getIsbn();
        } else if (std::dynamic_pointer_cast<Dvd>(item)) {
            type = "影音 (DVD)";
            auto dvd = std::dynamic_pointer_cast<Dvd>(item);
            details = "導演: " + dvd->getDirector() + " | 片長: " + std::to_string(dvd->getDuration()) + " 分鐘";
        } else if (std::dynamic_pointer_cast<Magazine>(item)) {
            type = "期刊 (Mag)";
            auto mag = std::dynamic_pointer_cast<Magazine>(item);
            details = "期號: " + std::to_string(mag->getIssueNum()) + " | 出版月份: " + std::to_string(mag->getMonth()) + "月";
        }

        std::cout << std::left << std::setw(8) << item->getId()
                  << std::setw(25) << (item->getTitle().length() > 22 ? item->getTitle().substr(0, 20) + ".." : item->getTitle())
                  << std::setw(10) << type
                  << std::setw(10) << (item->isBorrowedItem() ? "❌已借出" : "✅在庫")
                  << details << "\n";
    }
    std::cout << "------------------------------------------------------------\n";
    pause();
}


// User Action: Search media items
void LibrarySystem::searchInventory() const {
    std::cout << "請輸入搜尋關鍵字 (品名/作者/導演/類別): ";
    std::string query;
    std::getline(std::cin, query);
    query = trim(query);
    if (query.empty()) return;

    // Convert query to lower case
    std::string queryLower = query;
    std::transform(queryLower.begin(), queryLower.end(), queryLower.begin(), ::tolower);

    std::cout << "\n----------------------- 搜尋結果 -----------------------\n";
    bool found = false;
    for (const auto& item : inventory) {
        if (currentUser != nullptr && currentUser->getRole() == "USER" && item->getStatus() != "ACTIVE") {
            continue;
        }
        std::string titleLower = item->getTitle();
        std::transform(titleLower.begin(), titleLower.end(), titleLower.begin(), ::tolower);

        bool match = (titleLower.find(queryLower) != std::string::npos || item->getId() == query);
        
        std::string type = "";
        std::string details = "";
        if (std::dynamic_pointer_cast<Book>(item)) {
            type = "BOOK";
            auto book = std::dynamic_pointer_cast<Book>(item);
            std::string authorLower = book->getAuthor();
            std::transform(authorLower.begin(), authorLower.end(), authorLower.begin(), ::tolower);
            if (authorLower.find(queryLower) != std::string::npos) match = true;
            details = "作者: " + book->getAuthor() + " | ISBN: " + book->getIsbn();
        } else if (std::dynamic_pointer_cast<Dvd>(item)) {
            type = "DVD";
            auto dvd = std::dynamic_pointer_cast<Dvd>(item);
            std::string dirLower = dvd->getDirector();
            std::transform(dirLower.begin(), dirLower.end(), dirLower.begin(), ::tolower);
            if (dirLower.find(queryLower) != std::string::npos) match = true;
            details = "導演: " + dvd->getDirector() + " | 片長: " + std::to_string(dvd->getDuration()) + " 分鐘";
        } else if (std::dynamic_pointer_cast<Magazine>(item)) {
            type = "MAGAZINE";
            auto mag = std::dynamic_pointer_cast<Magazine>(item);
            details = "期號: " + std::to_string(mag->getIssueNum()) + " | 出版月份: " + std::to_string(mag->getMonth()) + "月";
        }

        std::string typeLower = type;
        std::transform(typeLower.begin(), typeLower.end(), typeLower.begin(), ::tolower);
        if (typeLower == queryLower) match = true;

        if (match) {
            found = true;
            std::cout << "[" << type << "] ID: " << item->getId() << " | 《" << item->getTitle() << "》 - " 
                      << (item->isBorrowedItem() ? "❌已借出" : "✅在庫") << " | " << details << "\n";
        }
    }
    if (!found) {
        std::cout << "無匹配的搜尋結果。\n";
    }
    std::cout << "--------------------------------------------------------\n";
    pause();
}


// User Action: Borrow item
void LibrarySystem::executeBorrow() {
    std::cout << "請輸入欲借閱的館藏 ID: ";
    std::string id;
    std::getline(std::cin, id);
    id = trim(id);

    // Find the item
    std::shared_ptr<MediaItem> target = nullptr;
    for (const auto& item : inventory) {
        if (item->getId() == id) {
            if (currentUser != nullptr && currentUser->getRole() == "USER" && item->getStatus() != "ACTIVE") {
                continue;
            }
            target = item;
            break;
        }
    }

    if (target == nullptr) {
        std::cout << "\n❌ 錯誤：找不到該館藏 ID。\n";
        pause();
        return;
    }

    if (target->isBorrowedItem()) {
        std::cout << "\n❌ 錯誤：該多媒體已被他人借出中。\n";
        pause();
        return;
    }

    // Cast current user to User derived class
    auto user = std::dynamic_pointer_cast<User>(currentUser);
    if (user == nullptr) return;

    // Perform borrow actions
    target->setBorrowed(true);
    user->addBorrowedId(id);

    // Create a new RentalRecord
    RentalRecord rec;
    int nextIndex = 10001 + allRecords.size();
    rec.recordId = "REC_" + std::to_string(nextIndex);
    rec.username = currentUser->getUsername();
    rec.itemId = id;
    rec.itemTitle = target->getTitle();
    rec.borrowDate = getTodayDateStr();
    rec.returnDate = "Pending";
    rec.rentalFee = 0.0;
    rec.status = "BORROWED";

    allRecords.push_back(rec);
    saveData();

    std::cout << "\n🎉 借閱成功！\n";
    std::cout << "交易編號: " << rec.recordId << "\n";
    std::cout << "借出項目: 《" << target->getTitle() << "》\n";
    std::cout << "借出日期: " << rec.borrowDate << "\n";
    pause();
}


// User Action: Return item
void LibrarySystem::executeReturn() {
    auto user = std::dynamic_pointer_cast<User>(currentUser);
    if (user == nullptr) return;

    const auto& borrowed = user->getBorrowedIds();
    if (borrowed.empty()) {
        std::cout << "\n您目前手頭沒有任何未歸還的借閱項目。\n";
        pause();
        return;
    }

    std::cout << "您手頭借用中的項目:\n";
    for (const auto& id : borrowed) {
        for (const auto& item : inventory) {
            if (item->getId() == id) {
                std::cout << "  - ID: " << id << " | 《" << item->getTitle() << "》\n";
            }
        }
    }

    std::cout << "請輸入欲歸還的館藏 ID: ";
    std::string id;
    std::getline(std::cin, id);
    id = trim(id);

    if (!user->removeBorrowedId(id)) {
        std::cout << "\n❌ 錯誤：輸入的 ID 不在您的借閱清單中。\n";
        pause();
        return;
    }

    // Update MediaItem status
    std::shared_ptr<MediaItem> target = nullptr;
    for (const auto& item : inventory) {
        if (item->getId() == id) {
            target = item;
            break;
        }
    }
    if (target != nullptr) {
        target->setBorrowed(false);
    }

    // Find the active RentalRecord and close it
    double calculatedFee = 0.0;
    int durationDays = 0;
    std::string today = getTodayDateStr();

    for (auto& rec : allRecords) {
        if (rec.username == currentUser->getUsername() && rec.itemId == id && rec.status == "BORROWED") {
            rec.returnDate = today;
            rec.status = "RETURNED";
            
            // Calculate rental fee using polymorphism!
            durationDays = calculateDaysBetween(rec.borrowDate, today);
            if (durationDays == 0) durationDays = 1; // Minimum 1 day rent fee
            
            if (target != nullptr) {
                calculatedFee = target->getFee(durationDays);
                rec.rentalFee = calculatedFee;
            }
            break;
        }
    }


    saveData();

    std::cout << "\n🎉 歸還成功！\n";
    std::cout << "歸還項目: 《" << (target ? target->getTitle() : "未知") << "》\n";
    std::cout << "借閱天數: " << durationDays << " 天\n";
    std::cout << "應付租金/滯納金: NT$ " << calculatedFee << " 元\n";
    pause();
}


// User Action: View rental records
void LibrarySystem::showUserRentalHistory() const {
    std::cout << "\n------------------- " << currentUser->getUsername() << " 的借閱歷史紀錄 -------------------\n";
    bool found = false;
    double unpaidTotal = 0.0;
    
    for (const auto& rec : allRecords) {
        if (rec.username == currentUser->getUsername()) {
            found = true;
            std::cout << "紀錄ID: " << rec.recordId << " | 《" << rec.itemTitle << "》(" << rec.itemId << ")\n";
            std::cout << "  - 借出日期: " << rec.borrowDate << " | 歸還日期: " << rec.returnDate << "\n";
            std::cout << "  - 狀態: " << (rec.status == "BORROWED" ? "❌ 借用中 (未還)" : "✅ 已歸還") << "\n";
            if (rec.status == "BORROWED") {
                // Calculate simulated current pending fee
                int days = calculateDaysBetween(rec.borrowDate, getTodayDateStr());
                if (days == 0) days = 1;
                
                double fee = 0.0;
                for (const auto& item : inventory) {
                    if (item->getId() == rec.itemId) {
                        fee = item->getFee(days);
                        break;
                    }
                }
                std::cout << "  - 當前累計租金: NT$ " << fee << " 元 (歸還時繳納)\n";
                unpaidTotal += fee;
            } else {
                std::cout << "  - 繳納租金: NT$ " << rec.rentalFee << " 元\n";
            }
            std::cout << "  --------------------------------------------------------\n";
        }
    }
    if (!found) {
        std::cout << "查無任何歷史交易紀錄。\n";
    } else {
        std::cout << ">>> 未歸還項目當前估計應繳租金總計: NT$ " << unpaidTotal << " 元\n";
    }
    std::cout << "--------------------------------------------------------------------\n";
    pause();
}


// Admin Action: Add new media item
void LibrarySystem::adminAddMedia() {
    std::cout << "請選擇新增的館藏類別:\n";
    std::cout << "  1. 圖書 (Book)\n";
    std::cout << "  2. 影音 (DVD)\n";
    std::cout << "  3. 期刊 (Magazine)\n";
    std::cout << "您的選擇 (1-3): ";
    std::string typeChoice;
    std::getline(std::cin, typeChoice);
    typeChoice = trim(typeChoice);

    if (typeChoice != "1" && typeChoice != "2" && typeChoice != "3") {
        std::cout << "❌ 錯誤：無效的類別選取。\n";
        pause();
        return;
    }

    std::cout << "請輸入新館藏 ID: ";
    std::string id;
    std::getline(std::cin, id);
    id = trim(id);

    // Check duplicate ID
    for (const auto& item : inventory) {
        if (item->getId() == id) {
            std::cout << "❌ 錯誤：ID 已存在，不可重複建立。\n";
            pause();
            return;
        }
    }

    std::cout << "請輸入館藏名稱/標題: ";
    std::string title;
    std::getline(std::cin, title);
    title = trim(title);

    if (typeChoice == "1") {
        std::cout << "請輸入作者: ";
        std::string author;
        std::getline(std::cin, author);
        author = trim(author);

        std::cout << "請輸入 ISBN: ";
        std::string isbn;
        std::getline(std::cin, isbn);
        isbn = trim(isbn);

        inventory.push_back(std::make_shared<Book>(id, title, false, author, isbn));
    } else if (typeChoice == "2") {
        std::cout << "請輸入導演: ";
        std::string director;
        std::getline(std::cin, director);
        director = trim(director);

        std::cout << "請輸入影片片長 (分鐘): ";
        std::string durationStr;
        std::getline(std::cin, durationStr);
        int duration = std::stoi(trim(durationStr));

        inventory.push_back(std::make_shared<Dvd>(id, title, false, director, duration));
    } else if (typeChoice == "3") {
        std::cout << "請輸入期刊期號: ";
        std::string issueStr;
        std::getline(std::cin, issueStr);
        int issue = std::stoi(trim(issueStr));

        std::cout << "請輸入期刊出版月份 (1-12): ";
        std::string monthStr;
        std::getline(std::cin, monthStr);
        int month = std::stoi(trim(monthStr));

        inventory.push_back(std::make_shared<Magazine>(id, title, false, issue, month));
    }

    saveData();
    std::cout << "\n🎉 館藏上架新增成功！\n";
    pause();
}


// Admin Action: Delete media item
void LibrarySystem::adminRemoveMedia() {
    std::vector<std::shared_ptr<MediaItem>> activeItems;
    for (const auto& item : inventory) {
        if (item->getStatus() == "ACTIVE") {
            activeItems.push_back(item);
        }
    }

    if (activeItems.empty()) {
        std::cout << "\n目前沒有任何上架中的館藏庫存可供下架。\n";
        pause();
        return;
    }

    std::vector<std::string> options;
    for (const auto& item : activeItems) {
        std::string type = "未知";
        if (std::dynamic_pointer_cast<Book>(item)) {
            type = "圖書";
        } else if (std::dynamic_pointer_cast<Dvd>(item)) {
            type = "影音";
        } else if (std::dynamic_pointer_cast<Magazine>(item)) {
            type = "期刊";
        }
        std::string opt = "[" + type + "] ID: " + item->getId() + " - " + item->getTitle();
        if (item->isBorrowedItem()) {
            opt += " (⚠️借出中)";
        }
        options.push_back(opt);
    }
    options.push_back("返回管理者主控台");

    std::string title = "\n===============================================\n"
                        "            【下架/刪除多媒體館藏】            \n"
                        "===============================================\n"
                        "請選擇欲下架刪除的項目:";
    int selection = getMenuSelection(options, title);

    if (selection == static_cast<int>(activeItems.size())) {
        return; // User cancelled
    }

    auto target = activeItems[selection];
    std::string id = target->getId();

    if (target->isBorrowedItem()) {
        std::cout << "⚠️ 警告：該館藏目前處於借出狀態，下架將強制收回並結清租用紀錄。\n";
        // Force remove from all users' borrowed lists
        for (auto& acc : accounts) {
            if (acc->getRole() == "USER") {
                auto user = std::dynamic_pointer_cast<User>(acc);
                user->removeBorrowedId(id);
            }
        }
    }

    target->setStatus("ARCHIVED");
    saveData();

    std::cout << "\n🎉 館藏 《" << target->getTitle() << "》 (ID: " << id << ") 已成功下架移至回收桶！\n";
    pause();
}


// Admin Action: View all system user accounts
void LibrarySystem::adminViewAllAccounts() const {
    std::cout << "\n----------------------- 系統註冊帳戶列表 -----------------------\n";
    std::cout << std::left << std::setw(15) << "帳號" << std::setw(10) << "密碼" << std::setw(10) << "角色" << "借閱明細 / 權限級別\n";
    std::cout << "--------------------------------------------------------------\n";
    for (const auto& acc : accounts) {
        std::string extra = "";
        if (acc->getRole() == "ADMIN") {
            auto admin = std::dynamic_pointer_cast<Admin>(acc);
            extra = "權限等級: " + std::to_string(admin->getAdminLevel());
        } else {
            auto user = std::dynamic_pointer_cast<User>(acc);
            const auto& borrowed = user->getBorrowedIds();
            if (borrowed.empty()) {
                extra = "無借用中項目";
            } else {
                extra = "借用中: ";
                for (size_t i = 0; i < borrowed.size(); ++i) {
                    extra += borrowed[i];
                    if (i < borrowed.size() - 1) extra += ", ";
                }
            }
        }

        std::cout << std::left << std::setw(15) << acc->getUsername()
                  << std::setw(10) << acc->getPassword()
                  << std::setw(10) << acc->getRole()
                  << extra << "\n";
    }
    std::cout << "--------------------------------------------------------------\n";
    pause();
}


// Admin Action: View all logs
void LibrarySystem::adminViewAllRecords() const {
    std::cout << "\n----------------------- 全系統借閱交易日誌 -----------------------\n";
    if (allRecords.empty()) {
        std::cout << "目前系統中無任何交易日誌紀錄。\n";
        pause();
        return;
    }
    
    std::cout << std::left << std::setw(10) << "紀錄ID" << std::setw(10) << "借閱者" << std::setw(8) << "館藏ID" << std::setw(25) << "標題" << std::setw(12) << "借書日期" << std::setw(12) << "還書日期" << std::setw(8) << "費用" << "狀態\n";
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    for (const auto& rec : allRecords) {
        std::cout << std::left << std::setw(10) << rec.recordId
                  << std::setw(10) << rec.username
                  << std::setw(8) << rec.itemId
                  << std::setw(25) << (rec.itemTitle.length() > 22 ? rec.itemTitle.substr(0, 20) + ".." : rec.itemTitle)
                  << std::setw(12) << rec.borrowDate
                  << std::setw(12) << rec.returnDate
                  << "NT$ " << std::left << std::setw(5) << rec.rentalFee
                  << rec.status << "\n";
    }
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    pause();
}


// Admin Action: Recycle Bin & Archive Management Center
void LibrarySystem::adminRecycleBinMenu() {
    while (true) {
        std::vector<std::string> options = {
            "檢視回收桶內容 (封存項目列表)",
            "還原重新上架已封存項目",
            "徹底清空回收桶 (硬刪除)",
            "返回管理者主控台"
        };
        std::string title = "\n===============================================\n"
                            "       【資源回收桶與封存管理中心】       \n"
                            "===============================================\n"
                            "請選擇操作項目:";
        int selection = getMenuSelection(options, title);

        if (selection == 0) {
            clearScreen();
            std::cout << "\n----------------------- 資源回收桶 (封存項目) -----------------------\n";
            std::vector<std::shared_ptr<MediaItem>> archivedItems;
            for (const auto& item : inventory) {
                if (item->getStatus() == "ARCHIVED") {
                    archivedItems.push_back(item);
                }
            }

            if (archivedItems.empty()) {
                std::cout << "資源回收桶目前是空的。\n";
            } else {
                std::cout << std::left << std::setw(8) << "ID" << std::setw(25) << "名稱" << std::setw(10) << "類別" << "詳細資料\n";
                std::cout << "-------------------------------------------------------------------\n";
                for (const auto& item : archivedItems) {
                    std::string type = "未知";
                    std::string details = "";
                    
                    if (std::dynamic_pointer_cast<Book>(item)) {
                        type = "圖書 (Book)";
                        auto book = std::dynamic_pointer_cast<Book>(item);
                        details = "作者: " + book->getAuthor() + " | ISBN: " + book->getIsbn();
                    } else if (std::dynamic_pointer_cast<Dvd>(item)) {
                        type = "影音 (DVD)";
                        auto dvd = std::dynamic_pointer_cast<Dvd>(item);
                        details = "導演: " + dvd->getDirector() + " | 片長: " + std::to_string(dvd->getDuration()) + " 分鐘";
                    } else if (std::dynamic_pointer_cast<Magazine>(item)) {
                        type = "期刊 (Mag)";
                        auto mag = std::dynamic_pointer_cast<Magazine>(item);
                        details = "期號: " + std::to_string(mag->getIssueNum()) + " | 出版月份: " + std::to_string(mag->getMonth()) + "月";
                    }

                    std::cout << std::left << std::setw(8) << item->getId()
                              << std::setw(25) << (item->getTitle().length() > 22 ? item->getTitle().substr(0, 20) + ".." : item->getTitle())
                              << std::setw(10) << type
                              << details << "\n";
                }
            }
            std::cout << "-------------------------------------------------------------------\n";
            pause();
        } else if (selection == 1) {
            std::vector<std::shared_ptr<MediaItem>> archivedItems;
            for (const auto& item : inventory) {
                if (item->getStatus() == "ARCHIVED") {
                    archivedItems.push_back(item);
                }
            }

            if (archivedItems.empty()) {
                std::cout << "\n資源回收桶目前沒有任何可還原的項目。\n";
                pause();
                continue;
            }

            std::vector<std::string> restoreOpts;
            for (const auto& item : archivedItems) {
                std::string type = "未知";
                if (std::dynamic_pointer_cast<Book>(item)) type = "圖書";
                else if (std::dynamic_pointer_cast<Dvd>(item)) type = "影音";
                else if (std::dynamic_pointer_cast<Magazine>(item)) type = "期刊";
                restoreOpts.push_back("[" + type + "] ID: " + item->getId() + " - " + item->getTitle());
            }
            restoreOpts.push_back("返回回收桶主選單");

            std::string restoreTitle = "\n===============================================\n"
                                       "            【還原重新上架已封存項目】            \n"
                                       "===============================================\n"
                                       "請選擇欲還原重新上架的項目:";
            int restoreSel = getMenuSelection(restoreOpts, restoreTitle);

            if (restoreSel == static_cast<int>(archivedItems.size())) {
                continue;
            }

            auto target = archivedItems[restoreSel];
            target->setStatus("ACTIVE");
            saveData();
            std::cout << "\n🎉 館藏 《" << target->getTitle() << "》 (ID: " << target->getId() << ") 已成功重新上架！\n";
            pause();
        } else if (selection == 2) {
            std::vector<std::shared_ptr<MediaItem>> archivedItems;
            for (const auto& item : inventory) {
                if (item->getStatus() == "ARCHIVED") {
                    archivedItems.push_back(item);
                }
            }

            if (archivedItems.empty()) {
                std::cout << "\n資源回收桶目前已經是空的。\n";
                pause();
                continue;
            }

            std::cout << "\n⚠️ 警告：您確定要徹底清空資源回收桶嗎？這將永久刪除 " << archivedItems.size() << " 個項目，且無法復原！\n";
            std::vector<std::string> confirmOpts = { "否 (取消)", "是 (確定清空)" };
            int confirmSel = getMenuSelection(confirmOpts, "請確認此危險操作:");
            
            if (confirmSel == 1) {
                inventory.erase(
                    std::remove_if(inventory.begin(), inventory.end(),
                        [](const std::shared_ptr<MediaItem>& item) {
                            return item->getStatus() == "ARCHIVED";
                        }
                    ),
                    inventory.end()
                );
                saveData();
                std::cout << "\n🎉 資源回收桶已徹底清空，所有封存項目已被硬刪除！\n";
                pause();
            } else {
                std::cout << "\n已取消清空操作。\n";
                pause();
            }
        } else if (selection == 3) {
            break;
        }
    }
}


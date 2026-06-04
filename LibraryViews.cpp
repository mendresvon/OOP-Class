#include "LibraryViews.h"

#include "LibrarySystem.h"
#include "media/Book.h"
#include "media/Dvd.h"
#include "media/Magazine.h"
#include "accounts/User.h"
#include "accounts/Admin.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace {
std::string toLowerCopy(const std::string& text) {
    std::string result = text;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return result;
}

std::string truncateTitle(const std::string& title) {
    return title.length() > 22 ? title.substr(0, 20) + ".." : title;
}

std::string borrowListText(const std::vector<std::string>& borrowed) {
    if (borrowed.empty()) {
        return "無借用中項目";
    }

    std::ostringstream oss;
    oss << "借用中: ";
    for (size_t i = 0; i < borrowed.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        oss << borrowed[i];
    }
    return oss.str();
}
}

void LibraryViews::showInventory(const LibrarySystem& system) {
    if (system.inventory.empty()) {
        std::cout << "\n目前圖書館沒有任何館藏庫存。\n";
        system.pause();
        return;
    }

    bool hasVisible = false;
    for (const auto& item : system.inventory) {
        if (system.currentUser != nullptr && system.currentUser->getRole() == "USER" && item->getStatus() != "ACTIVE") {
            continue;
        }
        hasVisible = true;
        break;
    }
    if (!hasVisible) {
        std::cout << "\n目前圖書館沒有任何館藏庫存。\n";
        system.pause();
        return;
    }

    std::cout << "\n----------------------- 圖書館館藏列表 -----------------------\n";
    std::cout << std::left << std::setw(8) << "ID" << std::setw(25) << "名稱" << std::setw(10) << "類別" << std::setw(10) << "狀態" << "詳細資料\n";
    std::cout << "------------------------------------------------------------\n";
    for (const auto& item : system.inventory) {
        if (system.currentUser != nullptr && system.currentUser->getRole() == "USER" && item->getStatus() != "ACTIVE") {
            continue;
        }

        std::string type = "未知";
        std::string details;

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
                  << std::setw(25) << truncateTitle(item->getTitle())
                  << std::setw(10) << type
                  << std::setw(10) << (item->isBorrowedItem() ? "❌已借出" : "✅在庫")
                  << details << "\n";
    }
    std::cout << "------------------------------------------------------------\n";
    system.pause();
}

void LibraryViews::searchInventory(const LibrarySystem& system) {
    std::cout << "請輸入搜尋關鍵字 (品名/作者/導演/類別): ";
    std::string query;
    std::getline(std::cin, query);
    query = system.trim(query);
    if (query.empty()) {
        return;
    }

    const std::string queryLower = toLowerCopy(query);

    std::cout << "\n----------------------- 搜尋結果 -----------------------\n";
    bool found = false;
    for (const auto& item : system.inventory) {
        if (system.currentUser != nullptr && system.currentUser->getRole() == "USER" && item->getStatus() != "ACTIVE") {
            continue;
        }

        std::string titleLower = toLowerCopy(item->getTitle());
        bool match = (titleLower.find(queryLower) != std::string::npos || item->getId() == query);

        std::string type;
        std::string details;
        if (std::dynamic_pointer_cast<Book>(item)) {
            type = "BOOK";
            auto book = std::dynamic_pointer_cast<Book>(item);
            if (toLowerCopy(book->getAuthor()).find(queryLower) != std::string::npos) {
                match = true;
            }
            details = "作者: " + book->getAuthor() + " | ISBN: " + book->getIsbn();
        } else if (std::dynamic_pointer_cast<Dvd>(item)) {
            type = "DVD";
            auto dvd = std::dynamic_pointer_cast<Dvd>(item);
            if (toLowerCopy(dvd->getDirector()).find(queryLower) != std::string::npos) {
                match = true;
            }
            details = "導演: " + dvd->getDirector() + " | 片長: " + std::to_string(dvd->getDuration()) + " 分鐘";
        } else if (std::dynamic_pointer_cast<Magazine>(item)) {
            type = "MAGAZINE";
            auto mag = std::dynamic_pointer_cast<Magazine>(item);
            details = "期號: " + std::to_string(mag->getIssueNum()) + " | 出版月份: " + std::to_string(mag->getMonth()) + "月";
        }

        std::string typeLower = toLowerCopy(type);
        if (typeLower == queryLower) {
            match = true;
        }

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
    system.pause();
}

void LibraryViews::showUserRentalHistory(const LibrarySystem& system) {
    std::cout << "\n------------------- " << system.currentUser->getUsername() << " 的借閱歷史紀錄 -------------------\n";
    bool found = false;
    double unpaidTotal = 0.0;

    for (const auto& rec : system.allRecords) {
        if (rec.username == system.currentUser->getUsername()) {
            found = true;
            std::cout << "紀錄ID: " << rec.recordId << " | 《" << rec.itemTitle << "》(" << rec.itemId << ")\n";
            std::cout << "  - 借出日期: " << rec.borrowDate << " | 歸還日期: " << rec.returnDate << "\n";
            std::cout << "  - 狀態: " << (rec.status == "BORROWED" ? "❌ 借用中 (未還)" : "✅ 已歸還") << "\n";
            if (rec.status == "BORROWED") {
                int days = system.calculateDaysBetween(rec.borrowDate, system.getTodayDateStr());
                if (days == 0) {
                    days = 1;
                }

                double fee = 0.0;
                for (const auto& item : system.inventory) {
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
    system.pause();
}

void LibraryViews::adminViewAllAccounts(const LibrarySystem& system) {
    std::cout << "\n----------------------- 系統註冊帳戶列表 -----------------------\n";
    std::cout << std::left << std::setw(15) << "帳號" << std::setw(10) << "角色" << "借閱明細 / 權限級別\n";
    std::cout << "-------------------------------------------------------\n";
    for (const auto& acc : system.accounts) {
        std::string extra;
        if (acc->getRole() == "ADMIN") {
            auto admin = std::dynamic_pointer_cast<Admin>(acc);
            extra = "權限等級: " + std::to_string(admin != nullptr ? admin->getAdminLevel() : 1);
        } else {
            auto user = std::dynamic_pointer_cast<User>(acc);
            extra = borrowListText(user != nullptr ? user->getBorrowedIds() : std::vector<std::string>{});
        }

        std::cout << std::left << std::setw(15) << acc->getUsername()
                  << std::setw(10) << acc->getRole()
                  << extra << "\n";
    }
    std::cout << "-------------------------------------------------------\n";
    system.pause();
}

void LibraryViews::adminViewAllRecords(const LibrarySystem& system) {
    std::cout << "\n----------------------- 全系統借閱交易日誌 -----------------------\n";
    if (system.allRecords.empty()) {
        std::cout << "目前系統中無任何交易日誌紀錄。\n";
        system.pause();
        return;
    }

    std::cout << std::left << std::setw(10) << "紀錄ID" << std::setw(10) << "借閱者" << std::setw(8) << "館藏ID" << std::setw(25) << "標題" << std::setw(12) << "借書日期" << std::setw(12) << "還書日期" << std::setw(8) << "費用" << "狀態\n";
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    for (const auto& rec : system.allRecords) {
        std::cout << std::left << std::setw(10) << rec.recordId
                  << std::setw(10) << rec.username
                  << std::setw(8) << rec.itemId
                  << std::setw(25) << truncateTitle(rec.itemTitle)
                  << std::setw(12) << rec.borrowDate
                  << std::setw(12) << rec.returnDate
                  << "NT$ " << std::left << std::setw(5) << rec.rentalFee
                  << rec.status << "\n";
    }
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    system.pause();
}

#include "LibraryOperations.h"

#include "LibrarySystem.h"
#include "media/Book.h"
#include "media/Dvd.h"
#include "media/Magazine.h"
#include "accounts/User.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

void LibraryOperations::executeBorrow(LibrarySystem& system) {
    std::cout << "請輸入欲借閱的館藏 ID: ";
    std::string id;
    std::getline(std::cin, id);
    id = system.trim(id);

    std::shared_ptr<MediaItem> target = nullptr;
    for (const auto& item : system.inventory) {
        if (item->getId() == id) {
            if (system.currentUser != nullptr && system.currentUser->getRole() == "USER" && item->getStatus() != "ACTIVE") {
                continue;
            }
            target = item;
            break;
        }
    }

    if (target == nullptr) {
        std::cout << "\n❌ 錯誤：找不到該館藏 ID。\n";
        system.pause();
        return;
    }

    if (target->isBorrowedItem()) {
        std::cout << "\n❌ 錯誤：該多媒體已被他人借出中。\n";
        system.pause();
        return;
    }

    auto user = std::dynamic_pointer_cast<User>(system.currentUser);
    if (user == nullptr) {
        return;
    }

    target->setBorrowed(true);
    user->addBorrowedId(id);

    RentalRecord rec;
    int nextIndex = 10001 + system.allRecords.size();
    rec.recordId = "REC_" + std::to_string(nextIndex);
    rec.username = system.currentUser->getUsername();
    rec.itemId = id;
    rec.itemTitle = target->getTitle();
    rec.borrowDate = system.getTodayDateStr();
    rec.returnDate = "Pending";
    rec.rentalFee = 0.0;
    rec.status = "BORROWED";

    system.allRecords.push_back(rec);
    system.saveData();

    std::cout << "\n🎉 借閱成功！\n";
    std::cout << "交易編號: " << rec.recordId << "\n";
    std::cout << "借出項目: 《" << target->getTitle() << "》\n";
    std::cout << "借出日期: " << rec.borrowDate << "\n";
    system.pause();
}

void LibraryOperations::executeReturn(LibrarySystem& system) {
    auto user = std::dynamic_pointer_cast<User>(system.currentUser);
    if (user == nullptr) {
        return;
    }

    const auto& borrowed = user->getBorrowedIds();
    if (borrowed.empty()) {
        std::cout << "\n您目前手頭沒有任何未歸還的借閱項目。\n";
        system.pause();
        return;
    }

    std::cout << "您手頭借用中的項目:\n";
    for (const auto& itemId : borrowed) {
        for (const auto& item : system.inventory) {
            if (item->getId() == itemId) {
                std::cout << "  - ID: " << itemId << " | 《" << item->getTitle() << "》\n";
            }
        }
    }

    std::cout << "請輸入欲歸還的館藏 ID: ";
    std::string id;
    std::getline(std::cin, id);
    id = system.trim(id);

    if (!user->removeBorrowedId(id)) {
        std::cout << "\n❌ 錯誤：輸入的 ID 不在您的借閱清單中。\n";
        system.pause();
        return;
    }

    std::shared_ptr<MediaItem> target = nullptr;
    for (const auto& item : system.inventory) {
        if (item->getId() == id) {
            target = item;
            break;
        }
    }
    if (target != nullptr) {
        target->setBorrowed(false);
    }

    double calculatedFee = 0.0;
    int durationDays = 0;
    std::string today = system.getTodayDateStr();

    for (auto& rec : system.allRecords) {
        if (rec.username == system.currentUser->getUsername() && rec.itemId == id && rec.status == "BORROWED") {
            rec.returnDate = today;
            rec.status = "RETURNED";
            durationDays = system.calculateDaysBetween(rec.borrowDate, today);
            if (durationDays == 0) {
                durationDays = 1;
            }
            if (target != nullptr) {
                calculatedFee = target->getFee(durationDays);
                rec.rentalFee = calculatedFee;
            }
            break;
        }
    }

    system.saveData();

    std::cout << "\n🎉 歸還成功！\n";
    std::cout << "歸還項目: 《" << (target ? target->getTitle() : "未知") << "》\n";
    std::cout << "借閱天數: " << durationDays << " 天\n";
    std::cout << "應付租金/滯納金: NT$ " << calculatedFee << " 元\n";
    system.pause();
}

void LibraryOperations::adminAddMedia(LibrarySystem& system) {
    std::cout << "請選擇新增的館藏類別:\n";
    std::cout << "  1. 圖書 (Book)\n";
    std::cout << "  2. 影音 (DVD)\n";
    std::cout << "  3. 期刊 (Magazine)\n";
    std::cout << "您的選擇 (1-3): ";
    std::string typeChoice;
    std::getline(std::cin, typeChoice);
    typeChoice = system.trim(typeChoice);

    if (typeChoice != "1" && typeChoice != "2" && typeChoice != "3") {
        std::cout << "❌ 錯誤：無效的類別選取。\n";
        system.pause();
        return;
    }

    std::cout << "請輸入新館藏 ID: ";
    std::string id;
    std::getline(std::cin, id);
    id = system.trim(id);

    for (const auto& item : system.inventory) {
        if (item->getId() == id) {
            std::cout << "❌ 錯誤：ID 已存在，不可重複建立。\n";
            system.pause();
            return;
        }
    }

    std::cout << "請輸入館藏名稱/標題: ";
    std::string title;
    std::getline(std::cin, title);
    title = system.trim(title);

    if (typeChoice == "1") {
        std::cout << "請輸入作者: ";
        std::string author;
        std::getline(std::cin, author);
        author = system.trim(author);

        std::cout << "請輸入 ISBN: ";
        std::string isbn;
        std::getline(std::cin, isbn);
        isbn = system.trim(isbn);

        system.inventory.push_back(std::make_shared<Book>(id, title, false, author, isbn));
    } else if (typeChoice == "2") {
        std::cout << "請輸入導演: ";
        std::string director;
        std::getline(std::cin, director);
        director = system.trim(director);

        std::cout << "請輸入影片片長 (分鐘): ";
        std::string durationStr;
        std::getline(std::cin, durationStr);
        int duration = std::stoi(system.trim(durationStr));

        system.inventory.push_back(std::make_shared<Dvd>(id, title, false, director, duration));
    } else {
        std::cout << "請輸入期刊期號: ";
        std::string issueStr;
        std::getline(std::cin, issueStr);
        int issue = std::stoi(system.trim(issueStr));

        std::cout << "請輸入期刊出版月份 (1-12): ";
        std::string monthStr;
        std::getline(std::cin, monthStr);
        int month = std::stoi(system.trim(monthStr));

        system.inventory.push_back(std::make_shared<Magazine>(id, title, false, issue, month));
    }

    system.saveData();
    std::cout << "\n🎉 館藏上架新增成功！\n";
    system.pause();
}

void LibraryOperations::adminRemoveMedia(LibrarySystem& system) {
    std::vector<std::shared_ptr<MediaItem>> activeItems;
    for (const auto& item : system.inventory) {
        if (item->getStatus() == "ACTIVE") {
            activeItems.push_back(item);
        }
    }

    if (activeItems.empty()) {
        std::cout << "\n目前沒有任何上架中的館藏庫存可供下架。\n";
        system.pause();
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
    int selection = system.getMenuSelection(options, title);

    if (selection == static_cast<int>(activeItems.size())) {
        return;
    }

    auto target = activeItems[selection];
    std::string id = target->getId();

    if (target->isBorrowedItem()) {
        std::cout << "⚠️ 警告：該館藏目前處於借出狀態，下架將強制收回並結清租用紀錄。\n";
        for (auto& acc : system.accounts) {
            if (acc->getRole() == "USER") {
                auto user = std::dynamic_pointer_cast<User>(acc);
                user->removeBorrowedId(id);
            }
        }
    }

    target->setStatus("ARCHIVED");
    system.saveData();

    std::cout << "\n🎉 館藏 《" << target->getTitle() << "》 (ID: " << id << ") 已成功下架移至回收桶！\n";
    system.pause();
}

void LibraryOperations::adminRecycleBinMenu(LibrarySystem& system) {
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
        int selection = system.getMenuSelection(options, title);

        if (selection == 0) {
            system.clearScreen();
            std::cout << "\n----------------------- 資源回收桶 (封存項目) -----------------------\n";
            std::vector<std::shared_ptr<MediaItem>> archivedItems;
            for (const auto& item : system.inventory) {
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
            system.pause();
        } else if (selection == 1) {
            std::vector<std::shared_ptr<MediaItem>> archivedItems;
            for (const auto& item : system.inventory) {
                if (item->getStatus() == "ARCHIVED") {
                    archivedItems.push_back(item);
                }
            }

            if (archivedItems.empty()) {
                std::cout << "\n資源回收桶目前沒有任何可還原的項目。\n";
                system.pause();
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
            int restoreSel = system.getMenuSelection(restoreOpts, restoreTitle);

            if (restoreSel == static_cast<int>(archivedItems.size())) {
                continue;
            }

            auto target = archivedItems[restoreSel];
            target->setStatus("ACTIVE");
            system.saveData();
            std::cout << "\n🎉 館藏 《" << target->getTitle() << "》 (ID: " << target->getId() << ") 已成功重新上架！\n";
            system.pause();
        } else if (selection == 2) {
            std::vector<std::shared_ptr<MediaItem>> archivedItems;
            for (const auto& item : system.inventory) {
                if (item->getStatus() == "ARCHIVED") {
                    archivedItems.push_back(item);
                }
            }

            if (archivedItems.empty()) {
                std::cout << "\n資源回收桶目前已經是空的。\n";
                system.pause();
                continue;
            }

            std::cout << "\n⚠️ 警告：您確定要徹底清空資源回收桶嗎？這將永久刪除 " << archivedItems.size() << " 個項目，且無法復原！\n";
            std::vector<std::string> confirmOpts = { "否 (取消)", "是 (確定清空)" };
            int confirmSel = system.getMenuSelection(confirmOpts, "請確認此危險操作:");

            if (confirmSel == 1) {
                system.inventory.erase(
                    std::remove_if(system.inventory.begin(), system.inventory.end(),
                        [](const std::shared_ptr<MediaItem>& item) {
                            return item->getStatus() == "ARCHIVED";
                        }),
                    system.inventory.end());
                system.saveData();
                std::cout << "\n🎉 資源回收桶已徹底清空，所有封存項目已被硬刪除！\n";
                system.pause();
            } else {
                std::cout << "\n已取消清空操作。\n";
                system.pause();
            }
        } else if (selection == 3) {
            break;
        }
    }
}

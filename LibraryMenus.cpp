#include "LibraryMenus.h"

#include "LibrarySystem.h"
#include "LibraryOperations.h"
#include "LibraryViews.h"

#include <iostream>
#include <string>
#include <vector>

void LibraryMenus::runUserMenu(LibrarySystem& system) {
    std::vector<std::string> options = {
        "瀏覽所有館藏 (圖書/DVD/雜誌)",
        "搜尋館藏 (按關鍵字/類型)",
        "借閱多媒體 (輸入 ID)",
        "歸還多媒體 (輸入 ID)",
        "查看我的借閱紀錄 & 應付租金",
        "登出系統"
    };
    std::string title = "\n===============================================\n"
                        "   【使用者控制台】 歡迎, " + system.currentUser->getUsername() + "! (一般會員)\n"
                        "===============================================\n"
                        "請選擇操作項目:";
    int selection = system.getMenuSelection(options, title);

    if (selection == 0) {
        LibraryViews::showInventory(system);
    } else if (selection == 1) {
        LibraryViews::searchInventory(system);
    } else if (selection == 2) {
        LibraryOperations::executeBorrow(system);
    } else if (selection == 3) {
        LibraryOperations::executeReturn(system);
    } else if (selection == 4) {
        LibraryViews::showUserRentalHistory(system);
    } else if (selection == 5) {
        system.processLogout();
        std::cout << "\n已成功登出系統。\n";
        system.pause();
    }
}

void LibraryMenus::runAdminMenu(LibrarySystem& system) {
    std::vector<std::string> options = {
        "新增多媒體館藏 (圖書/DVD/雜誌)",
        "下架/刪除多媒體館藏",
        "查看所有使用者名單 & 借閱狀態",
        "檢視全館租借交易日誌 (Rental Log)",
        "資源回收桶與封存管理中心",
        "登出系統"
    };
    std::string title = "\n===============================================\n"
                        "      【管理者主控台】 歡迎, " + system.currentUser->getUsername() + "! (系統管理員)\n"
                        "===============================================\n"
                        "請選擇操作項目:";
    int selection = system.getMenuSelection(options, title);

    if (selection == 0) {
        LibraryOperations::adminAddMedia(system);
    } else if (selection == 1) {
        LibraryOperations::adminRemoveMedia(system);
    } else if (selection == 2) {
        LibraryViews::adminViewAllAccounts(system);
    } else if (selection == 3) {
        LibraryViews::adminViewAllRecords(system);
    } else if (selection == 4) {
        LibraryOperations::adminRecycleBinMenu(system);
    } else if (selection == 5) {
        system.processLogout();
        std::cout << "\n已成功登出系統。\n";
        system.pause();
    }
}

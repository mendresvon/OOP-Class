# 智慧型圖書/影音多媒體租借管理系統 (Smart Library & Media Rental System)

本專案是一個採用現代 C++（C++17）開發的模組化多媒體租借與會員權限管理系統。具備精緻的終端機 CLI 選單介面、檔案持久化、多型序列化與高階物件導向設計。

---

## 🏛️ 專案物理目錄架構 (File Directory)

*   `main.cpp` - 程式的啟動入口。
*   `LibrarySystem.h` / `.cpp` - 系統的核心控制器，負責處理 CLI 渲染、狀態管理與檔案儲存。
*   `RentalRecord.h` - 定義租借交易紀錄之輕量資料結構。
*   `media/` - 多媒體館藏模組目錄。
    *   `MediaItem.h` / `.cpp` - 館藏抽象基底類別。
    *   `Book.h` / `.cpp` - 圖書衍生類別（計算租金與 ISBN 屬性）。
    *   `Dvd.h` / `.cpp` - DVD 影音衍生類別（片長與導演屬性）。
    *   `Magazine.h` / `.cpp` - 期刊雜誌衍生類別（期號與出版月份）。
*   `accounts/` - 帳戶與權限模組目錄。
    *   `Account.h` / `.cpp` - 帳戶抽象基底類別。
    *   `User.h` / `.cpp` - 一般讀者類別（處理個人借還與借書清單）。
    *   `Admin.h` / `.cpp` - 系統管理員類別（管理庫存與檢視系統日誌）。
*   `data/` - 檔案資料庫儲存目錄。
    *   `inventory.txt` - 館藏實體資料庫。
    *   `accounts.txt` - 帳號密碼與權限資料庫。
    *   `rental_records.txt` - 全館交易日誌庫。

---

## 🔨 編譯指引 (Compilation Guide)

### 方法一：使用 CMake 建置 (跨平台推薦)
1.  建立建置目錄：
    ```bash
    mkdir build
    cd build
    ```
2.  配置專案：
    ```bash
    cmake ..
    ```
3.  執行編譯：
    ```bash
    cmake --build .
    ```
    *CMake 會自動將 `data/` 目錄複製到編譯目錄下，確保執行時路徑正確。*

### 方法二：使用 g++ 進行手動編譯
如果您沒有安裝 CMake，可直接在專案根目錄下使用 GCC/g++ 進行編譯：
```bash
g++ -std=c++17 -Wall main.cpp LibrarySystem.cpp media/MediaItem.cpp media/Book.cpp media/Dvd.cpp media/Magazine.cpp accounts/Account.cpp accounts/User.cpp accounts/Admin.cpp -o SmartLibrarySystem.exe
```

---

## 🚀 執行與快速登入測試帳號 (Quick Start)

編譯成功後，執行產出的二進位檔 `SmartLibrarySystem`：

```bash
# 執行程式
.\SmartLibrarySystem.exe  # Windows
./SmartLibrarySystem      # Linux / macOS
```

### 🔒 測試帳號列表
本系統提供以下預設的三組不同角色之帳戶：

1.  **系統管理員 (ADMIN)**:
    *   **帳號**：`admin`
    *   **密碼**：`admin123`
2.  **一般讀者 A (USER)**:
    *   **帳號**：`alex`
    *   **密碼**：`user123`
3.  **一般讀者 B (USER)**:
    *   **帳號**：`bob`
    *   **密碼**：`user123`

---

## ⌨️ 互動操作與安全機制說明 (User Interaction & Safety Features)

### 1. 🎹 鍵盤方向鍵互動選單
本系統之所有 CLI 控制選單已升級為「鍵盤上下鍵移動、反白高亮選取」的現代化鍵盤驅動介面：
*   **操作方式**：使用鍵盤 **[↑] (Up)** 與 **[↓] (Down)** 箭頭鍵上下移動游標，選中的項目會以反白高亮（ANSI `\033[7m`）顯示，按下 **[Enter]** 鍵即可確認執行該選項。
*   **密碼隱藏防窺**：於登入與註冊輸入密碼時，畫面會以 `*` 字元替代明碼顯示，且支援退格鍵（Backspace）進行修改，具備極佳的隱私保護與容錯率。

### 2. ♻️ 資源回收桶與軟刪除（Soft Delete）防呆機制
為了保障全館庫存的資料安全並降低誤刪風險，系統導入了高安全性的「軟刪除」架構：
*   **軟刪除（Soft Delete）**：當管理者下架刪除某項館藏時，該項目不會立刻從硬碟資料庫物理移除，而是將其狀態欄位變更為 `"ARCHIVED"`，並安全移入「資源回收桶」。軟下架項目對一般讀者在瀏覽、搜尋、借閱時完全不可見。
*   **還原重新上架（Restore）**：管理者可隨時進入「資源回收桶與封存管理中心」子選單，將先前封存的項目重新變更狀態為 `"ACTIVE"`，即時還原上架。
*   **徹底清空（Hard Purge）**：管理者可執行徹底清空回收桶操作，使用 C++ STL 之 `std::remove_if` 精準硬刪除所有被封存的項目，並即時改寫檔案以完成持久化物理刪除，釋放資源。

---

## 💎 系統核心亮點 (Core Architecture Features)

1.  **多型序列化技術**：基底類別宣告虛擬函數 `serialize() = 0`，衍生多媒體物件（Book/Dvd/Magazine）自我格式化，主控制器使用迴圈輸出同一 `vector<shared_ptr>` 即完成多型檔案儲存。
2.  **物件工廠載入技術**：檔案讀取時解析標籤欄位（如 BOOK/DVD），動態載入並實體化對應之衍生多型物件。
3.  **租金/滯納金多型計算**：每種多媒體擁有不同的計費邏輯與超期加乘公式，透過 `item->getFee(days)` 於還書時自動結算費用。
4.  **智慧型指標記憶體防漏**：捨棄 Raw Pointer，全專案均採用 `std::shared_ptr` 與 `std::unique_ptr` 進行資源生命週期控管，完全杜絕 Memory Leak。

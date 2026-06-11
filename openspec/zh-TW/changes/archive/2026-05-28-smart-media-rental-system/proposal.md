## Why

當前的專案需要一個結構化、模組化且具備持久化功能的智慧型圖書/影音多媒體租借管理系統。為了學習並展現 C++ 物件導向程式設計（OOP）、標準模板庫（STL）應用以及檔案 I/O 技術，本專案將建構一個具備使用者與管理者雙角色權限、完整終端機 CLI 互動介面，並採用 CMake 建置系統的跨平台應用程式。

## What Changes

- **物件導向設計 (OOP)**：設計多媒體館藏繼承體系（`MediaItem` -> `Book` / `Dvd` / `Magazine`）與帳戶權限繼承體系（`Account` -> `User` / `Admin`），每個類別皆以獨立檔案（`.h` / `.cpp`）進行分離。
- **租借與日誌紀錄系統 (Rental Logging)**：引入 `RentalRecord` 結構體，追蹤每次借還書時間、歸還天數、租金計算及逾期狀態，供使用者與管理員進行統計查詢。
- **檔案持久化 (File Persistence)**：使用 C++ 檔案 I/O（`std::ifstream`, `std::ofstream`）實現館藏庫存、帳戶資料與租借歷史紀錄的硬碟讀寫，防範當機或重啟導致資料遺失。
- **精緻終端機介面 (CLI Interface)**：提供直覺式選單，支援登入、註冊、多型館藏檢索、借還流程、租借歷史追蹤以及管理員館藏與系統日誌管理。
- **CMake 自動化建置**：導入 `CMakeLists.txt` 管理多檔案與多目錄的編譯流程，並實作編譯期自動將測試用資料檔案（`data/` 目錄）複製至輸出目錄之建置配置。

## Capabilities

### New Capabilities
- `media-rental-system`: 提供圖書（Book）、影音（DVD）與期刊（Magazine）的多型館藏物件管理與搜尋檢索。
- `account-management`: 提供使用者與管理者的註冊、登入驗證、登出，以及針對不同角色的 CLI 功能選單分流。
- `rental-history-records`: 負責追蹤與記錄每次的借閱活動，支援租金與逾期的動態計算，並完成檔案讀寫之持久化。
- `cmake-build-documentation`: 提供標準的 CMakeLists.txt 配置與對應的編譯安裝流程使用指南（README.md）。

### Modified Capabilities
<!-- 無 -->

## Impact

- **新增建置配置**：新增 `CMakeLists.txt` 以做為專案編譯核心。
- **新增多媒體與帳戶模組**：於 `media/` 與 `accounts/` 資料夾下新增各自的類別檔案。
- **新增資料儲存庫**：於 `data/` 資料夾下儲存 `inventory.txt`、`accounts.txt` 與 `rental_records.txt` 等持久化純文字檔。
- **說明文件**：於專案根目錄新增 `README.md`，提供完整的安裝、編譯、執行及架構介紹說明。

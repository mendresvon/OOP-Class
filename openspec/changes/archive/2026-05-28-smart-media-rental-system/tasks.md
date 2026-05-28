## 1. 專案基礎建設與 CMake 配置

- [x] 1.1 建立物理資料夾結構（建立 media、accounts 與 data 資料夾）
- [x] 1.2 建立初始 mock 資料文字檔案（data/inventory.txt, data/accounts.txt, data/rental_records.txt）
- [x] 1.3 建立與配置根目錄 CMakeLists.txt，實作資源自動拷貝 (data 拷貝至 build)


## 2. 媒體館藏模組 (Media Item Module) 實作

- [x] 2.1 實作基底類別 MediaItem，提供多型 serialize 序列化與 getFee 租金虛擬函數
- [x] 2.2 實作衍生類別 Book 類別與分離式實作檔，並提供專屬 Book 序列化欄位
- [x] 2.3 實作衍生類別 Dvd 類別與分離式實作檔，並提供專屬 Dvd 序列化欄位
- [x] 2.4 實作衍生類別 Magazine 類別與分離式實作檔，並提供專屬 Magazine 序列化欄位


## 3. 帳戶權限模組 (Account Module) 實作

- [x] 3.1 實作基底類別 Account，提供多型角色回傳（getRole）與顯示選單（showMenu）虛擬函數
- [x] 3.2 實作衍生類別 User，定義使用者借閱清單與一般使用者專屬 CLI 選單
- [x] 3.3 實作衍生類別 Admin，定義管理者權限層級與管理者專屬 CLI 管理選單


## 4. 租借紀錄模組 (Rental Record) 與檔案 I/O 實作

- [x] 4.1 定義交易紀錄 RentalRecord 結構體，包含編號、借還時間、租金與狀態
- [x] 4.2 於 LibrarySystem 中實作 loadData 函數，使用 Stringstream 與檔案串流載入並解析三類資料
- [x] 4.3 於 LibrarySystem 中實作 saveData 函數，完成多型序列化寫回檔案機制

## 5. 系統主控與終端選單 (Library System & CLI) 實作

- [x] 5.1 實作 LibrarySystem 註冊、登入與登出流程，對應設置 `currentUser` 狀態
- [x] 5.2 實作一般使用者借閱多型館藏、歸還多型館藏邏輯，並串接 getFee 計算所產生之費用
- [x] 5.3 實作管理員館藏增刪（CRUD）管理、查看所有用戶借閱狀態及全館租借交易日誌
- [x] 5.4 實作 main.cpp，初始化 LibrarySystem 並正式運行應用程式無窮 CLI 迴圈


## 6. 編譯、測試與安裝文件撰寫

- [x] 6.1 使用 CMake 進行 out-of-source 編譯與連結，排除所有編譯警告
- [x] 6.2 執行模擬借書、還書、管理員 CRUD 等動作，確認檔案持久化正確
- [x] 6.3 於專案根目錄撰寫完整的 README.md 流程指引與安裝部署文件


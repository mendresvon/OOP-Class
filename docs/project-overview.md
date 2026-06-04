# 專案總覽

## 系統目標

本專案為智慧型圖書/影音租借管理系統，支援一般使用者與管理者角色操作，並提供 `kv-v1` 檔案持久化與安全驗證。

## 核心模組

- 媒體模組：`MediaItem`、`Book`、`Dvd`、`Magazine`
- 帳戶模組：`Account`、`User`、`Admin`
- 系統協調：`LibrarySystem`
- 選單流程：`LibraryMenus`
- 業務處理：`LibraryService`、`LibraryOperations`
- 查詢顯示：`LibraryViews`
- CLI 互動：`MenuRenderer`
- 持久化資料：`data/inventory.txt`、`data/accounts.txt`、`data/rental_records.txt`

## 近期改造方向

- 持久化格式升級為 `kv-v1`
- 導入值轉義規則（`\\`、`\|`、`\=`、`\n`、`\r`）
- 密碼改為雜湊加鹽儲存
- `LibrarySystem` 進行職責拆分（Coordinator / Menus / Views / Operations）
- 文件治理與 Doc Sync Gate 導入

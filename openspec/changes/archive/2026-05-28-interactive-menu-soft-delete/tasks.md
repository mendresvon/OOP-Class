## 1. 媒體館藏結構與序列化升級 (Media Module Upgrade)

- [x] 1.1 於 `MediaItem` 基底類別新增 `status` 屬性（預設值為 `"ACTIVE"`），並提供 getter 與 setter
- [x] 1.2 修改 `Book`、`Dvd` 與 `Magazine` 的 `serialize` 多型實作，於每筆資料末尾附加 `status` 屬性
- [x] 1.3 升級 `LibrarySystem::loadData`，實作狀態解析容錯（若欄位不足自動設為 `"ACTIVE"`），並升級 `saveData` 配合寫回欄位


## 2. 鍵盤互動選單設計 (Keyboard CLI Menu)

- [x] 2.1 於 `LibrarySystem` 中實作通用鍵盤監聽高亮選單 `getMenuSelection`，處理上下方向鍵與反白渲染
- [x] 2.2 重構 `LibrarySystem::run`，將登入前的主控制選單改為鍵盤高亮選取模式
- [x] 2.3 重構一般使用者控制選單 `runUserMenu`，改為鍵盤高亮選取模式
- [x] 2.4 重構管理員主控選單 `runAdminMenu`，改為鍵盤高亮選取模式

## 3. 資源回收桶與封存管理實作 (Recycle Bin & Archive Management)

- [x] 3.1 修改 `LibrarySystem::showInventory` 與 `searchInventory`，僅對一般讀者顯示 `status == "ACTIVE"` 的館藏
- [x] 3.2 實作管理員子選單「資源回收桶與封存管理中心」之選單渲染與控制迴圈
- [x] 3.3 重構管理者「下架刪除多媒體項目」改為軟刪除（變更 `status` 為 `"ARCHIVED"`），並支援鍵盤高亮選取項目
- [x] 3.4 實作回收桶「還原重新上架已封存項目」功能，支援鍵盤高亮選取項目
- [x] 3.5 實作回收桶「徹底清空回收桶」功能，使用 STL `std::remove_if` 硬刪除所有 `"ARCHIVED"` 物件

## 4. 編譯、整合測試與文件更新

- [x] 4.1 執行 out-of-source 編譯，確認鍵盤方向鍵監聽與選單零警告通過編譯
- [x] 4.2 執行借書、還書、軟下架、回收桶檢視、還原上架與清空之整合測試，確認資料持久化狀態完全正確
- [x] 4.3 更新 README.md 文件，新增「鍵盤上下鍵操作說明」與「資源回收桶軟刪除機制介紹」

## Why

當前的系統在刪除多媒體項目時會立即在硬碟資料庫中將其移除，這缺乏了防止誤刪的安全機制。此外，目前的 CLI 介面依賴傳統的文字數字輸入，在體驗上較為繁瑣。本提案旨在為系統導入「軟刪除」與「資源回收桶」管理機制，並將終端機 CLI 選單全面升級為支援「鍵盤上下鍵移動、高亮反白選取」的現代化極致互動體驗。

## What Changes

- **鍵盤方向鍵互動選單 (BREAKING - CLI)**：移除傳統以數字鍵盤輸入指令的方式，全面改為監聽方向鍵（[↑][↓]）來進行功能與項目的高亮反白（ANSI 7m 控制碼）選取，按下 Enter 鍵確認。
- **單一陣列狀態標籤 (Status Tag)**：在 `MediaItem` 基底類別新增 `status` 屬性（`"ACTIVE"` / `"ARCHIVED"`），統一資料儲存與讀寫。
- **資源回收桶 (Recycle Bin - Soft Delete & Restore)**：下架項目時改為標記為 `"ARCHIVED"`（置入回收桶，使用者端隱形）；新增管理者「資源回收桶與封存管理中心」子選單，支援檢視回收桶、項目重新上架（還原）及徹底硬清空功能。

## Capabilities

### New Capabilities
- `recycle-bin-persistence`: 提供回收桶硬清空、單一檔案持久化與狀態追蹤支援。

### Modified Capabilities
- `media-rental-system`: 新增 `status` 標記、軟下架封存（Soft Delete）與重新上架（Restore）多型管理。
- `account-management`: 管理者選單與使用者選單全面升級為方向鍵反白高亮選取，並為管理者新增「封存管理中心」二級選單。

## Impact

- **物理代碼異動**：修改 `MediaItem.h/cpp`（新增狀態欄位與序列化格式）、`LibrarySystem.h/cpp`（新增 `getMenuSelection` 通用選單、修改借還、增刪、軟刪除、還原等 CLI 互動邏輯）。
- **資料檔案異動**：`data/inventory.txt` 將在每行末尾多出一個 `,ACTIVE` 或 `,ARCHIVED` 狀態字串，程式啟動時載入工廠亦需對應修改解析。

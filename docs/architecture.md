# 架構設計

## 目標分層

- 協調層：`LibrarySystem`（啟動流程、登入註冊、load/save 呼叫）
- 選單層：`MenuRenderer` + `LibraryMenus`（CLI 互動與角色選單）
- 業務層：`LibraryService` + `LibraryOperations`（驗證、借還、管理流程）
- 查詢/報表層：`LibraryViews`（館藏查詢、帳號清單、交易紀錄）
- 持久化層：`PersistenceRepository`（`kv-v1` 解析、嚴格驗證、容錯、回滾）

## 依賴方向

Menus/Views/Operations -> LibrarySystem（受控存取）

LibrarySystem -> Service/Repository

## 責任邊界

- `LibrarySystem`：不直接承載借還、查詢、報表或角色選單迴圈
- `LibraryMenus`：角色選單流程與操作分派
- `LibraryViews`：純顯示與查詢輸出
- `LibraryOperations`：借還、新增、下架、回收桶管理
- `LibraryService`：登入/註冊驗證
- `PersistenceRepository`：資料檔讀寫與可靠性保護

## 設計原則

1. 單一職責：每層只做該層職責。
2. 可測試性：業務與 I/O 分離。
3. 可維護性：變更影響範圍可預期。

## 文件治理與驗證整合

- 本機 Doc Sync Gate：`scripts/check-doc-sync.ps1`
- CI Doc Sync Gate：`.github/workflows/doc-sync-gate.yml`
- CMake 驗證目標：`doc_sync_gate`、`run_kv_tests`

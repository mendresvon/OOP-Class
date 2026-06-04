## 1. 規格與格式定義

- [x] 1.1 定義 `kv-v1` 檔案格式（inventory/accounts/rental_records）與必要鍵名
- [x] 1.2 定義欄位轉義規則（`|`、`=`、換行）與空值策略
- [x] 1.3 定義穩定輸出欄位順序與版本標頭規範

## 2. 解析與序列化層

- [x] 2.1 建立 `FieldMap` 解析器（string -> unordered_map）
- [x] 2.2 建立 domain 映射器（FieldMap <-> MediaItem/Account/RentalRecord）
- [x] 2.3 建立 `kv-v1` 嚴格格式驗證（缺版本標頭或缺必要鍵名即回報）
- [x] 2.4 建立錯誤行收集與診斷輸出機制

## 3. 持久化可靠性

- [x] 3.1 導入暫存檔寫入與 rename 原子替換流程
- [x] 3.2 實作多檔案寫入失敗回滾保護策略
- [x] 3.3 在流程中加入 I/O 錯誤可見提示

## 4. 帳戶安全

- [x] 4.1 導入密碼雜湊與鹽值欄位（`passwordHash`、`passwordSalt`）
- [x] 4.2 移除明文密碼儲存與管理頁顯示
- [x] 4.3 登入流程改為雜湊比對，補充錯誤訊息

## 5. LibrarySystem 拆責任

- [x] 5.1 拆分 `MenuRenderer`（CLI 顯示/輸入）
- [x] 5.2 拆分 `LibraryService`（借還、搜尋、管理業務）
- [x] 5.3 拆分 `PersistenceRepository`（格式解析與檔案讀寫）
- [x] 5.4 讓 `LibrarySystem` 僅保留流程協調

## 6. 測試與文件

- [x] 6.1 建立 `kv-v1` 嚴格格式測試案例（不含舊格式相容）
- [x] 6.2 建立壞資料容錯測試案例
- [x] 6.3 建立密碼不落地明文的驗證案例
- [x] 6.4 更新 README 的資料格式、安全與操作章節
- [x] 6.5 更新變更文件（proposal/design/tasks）與對應 capability spec

## 7. 文件同步治理機制

- [x] 7.1 建立文件覆蓋矩陣（功能類型 -> 必須更新的文件）
- [x] 7.2 建立 Doc Sync Gate 檢查腳本或 CI 任務
- [x] 7.3 建立變更完成檢核清單（DoD 必含文件同步）
- [x] 7.4 將 Doc Sync Gate 納入日常建置/驗證流程

## 8. 專案層文件產出（固定 docs 目錄）

- [x] 8.1 建立 `docs/` 固定文件資料夾
- [x] 8.2 建立 `docs/project-overview.md` 與 `docs/architecture.md`
- [x] 8.3 建立 `docs/data-format-kv-v1.md` 與 `docs/security-authentication.md`
- [x] 8.4 建立 `docs/testing-validation.md` 與 `docs/changelog.md`
- [x] 8.5 將文件覆蓋矩陣與 DoD 檢核關聯到 `docs/` 流程
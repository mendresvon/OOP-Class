# 文件覆蓋矩陣（初版）

## 目的

本矩陣定義各類型變更所對應的必更文件。
若對應文件未同步更新，該變更不得視為完成。

## 覆蓋矩陣

| 變更類型 | 常見觸發檔案 | 必須同步更新的文件 |
|---|---|---|
| 使用者可見行為 / CLI 流程 | `LibrarySystem.cpp`, `main.cpp`, `accounts/*.cpp`, `media/*.cpp` | `README.md`（使用方式/流程章節）、該變更的 `tasks.md` 進度註記 |
| 資料格式 / 持久化欄位 | `LibrarySystem.cpp`, `data/*.txt`, 後續 repository/parser 檔案 | 該變更的 `design.md`、`specs/stl-structured-persistence/spec.md`、`README.md` 資料格式章節 |
| 驗證 / 密碼處理 | `accounts/*.cpp`, `LibrarySystem.cpp` | `specs/account-management/spec.md`、`README.md` 安全章節 |
| 架構邊界 / 職責調整 | `LibrarySystem.*`, 新增 service/repository/renderer 檔案 | 該變更的 `design.md`、`specs/library-system-architecture/spec.md` |
| 錯誤處理 / 韌性策略 | parser/load-save 邏輯、驗證邏輯 | `design.md`（風險/驗證章節）、相關 capability spec 的 Scenario 更新 |
| 建置 / 工具鏈 / 流程關卡 | `CMakeLists.txt`, CI/workflow 腳本、檢查腳本 | `README.md` 建置/流程章節、`specs/documentation-governance/spec.md` |
| 測試策略 / 驗證標準 | 測試檔案、驗證腳本 | 該變更的 `tasks.md` 測試檢核項、`README.md` 測試章節 |
| 範圍或需求調整 | 任一 capability 層級行為改動 | 該變更的 `proposal.md`、`specs/` 下受影響 capability 規格 |

## 每次變更最小文件集合

只要有程式碼變更，至少要更新以下其中一類：
- `README.md`
- 當前變更文件：`proposal.md`、`design.md`、`tasks.md`
- `openspec/changes/<change>/specs/` 下至少一份受影響 capability 規格

若是安全或資料格式變更，以下兩項都必須更新：
- `README.md` 對應章節
- 對應 capability 的 spec 檔案

## 審查者快速檢查

1. 確認本次程式變更可對應到本矩陣至少一列。
2. 確認該列要求的文件都在同一變更中已更新。
3. 若有缺漏，拒絕結案並要求補齊文件同步。

## 角色責任

- 實作者：在同一變更中完成程式與文件更新。
- 審查者：在核准前驗證矩陣覆蓋完整。
- 維護者：當新增模組類型時，更新本矩陣。

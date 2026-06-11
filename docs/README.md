# 文件目錄（docs）

`docs/` 是專案層文件固定路徑，所有架構、資料格式、安全與測試說明都維持在此目錄。

## 文件清單

- `project-overview.md`：專案目標、模組與責任概覽
- `architecture.md`：分層架構與依賴方向
- `data-format-kv-v1.md`：`kv-v1` 格式、必要鍵、轉義規則
- `security-authentication.md`：帳戶認證與密碼安全
- `testing-validation.md`：測試策略、測試腳本、日常驗證流程
- `changelog.md`：版本與重要變更紀錄

## 文件覆蓋矩陣（Task 7.1）

| 變更類型 | 必須更新文件 |
|---|---|
| 使用者流程/操作行為 | `README.md`, `docs/project-overview.md`, `docs/testing-validation.md` |
| 資料格式（kv-v1、鍵名、轉義） | `README.md`, `docs/data-format-kv-v1.md`, `openspec/specs/stl-structured-persistence/spec.md` |
| 安全策略（雜湊/鹽值/登入驗證） | `README.md`, `docs/security-authentication.md`, `openspec/specs/account-management/spec.md` |
| 架構邊界（模組拆分/依賴方向） | `docs/architecture.md`, `openspec/specs/library-system-architecture/spec.md`, `openspec/specs/media-rental-system/spec.md` |
| 測試策略與驗證流程 | `docs/testing-validation.md`, `openspec/changes/*/tasks.md` |

## DoD 檢核清單（Task 7.3）

每次變更在標記完成前，必須全部成立：

1. 功能或重構已完成並可編譯。
2. 對應測試已新增或更新，且可執行。
3. 對應文件（依覆蓋矩陣）已更新。
4. `scripts/check-doc-sync.ps1` 檢查通過。
5. OpenSpec 的 `tasks.md` 與相關 capability spec 已同步。

## Doc Sync Gate

- 本機執行：`scripts/check-doc-sync.ps1`
- CI 執行：`.github/workflows/doc-sync-gate.yml`
- CMake 目標：`doc_sync_gate`

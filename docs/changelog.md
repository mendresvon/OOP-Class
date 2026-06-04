# 變更紀錄

## 2026-06-04

### 新增

- 建立 `docs/` 固定文件目錄
- 新增專案層文件：總覽、架構、資料格式、安全、測試、變更紀錄
- 新增 `scripts/run-kv-tests.ps1` 自動化驗證腳本
- 新增 `scripts/check-doc-sync.ps1` 文件同步檢查腳本
- 新增 CI workflow：`.github/workflows/doc-sync-gate.yml`
- 新增 capability specs：
	- `openspec/specs/stl-structured-persistence/spec.md`
	- `openspec/specs/library-system-architecture/spec.md`
	- `openspec/specs/documentation-governance/spec.md`

### 規格

- 專案層文件正式納入 `2026-06-04-stl-data-format-hardening` 變更規格
- 文件治理新增 `docs/` 固定路徑要求

### 實作

- `kv-v1` 解析加入必要鍵嚴格驗證與錯誤診斷輸出
- `kv-v1` 值支援跳脫與反跳脫
- 多檔寫入失敗加入 `.bak` 回滾機制

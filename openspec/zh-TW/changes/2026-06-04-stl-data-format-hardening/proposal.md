## 為什麼要做

目前系統使用 CSV-like 純文字格式做持久化，存在三個主要問題：
- 欄位以逗號切分，當標題或名稱含逗號時易解析錯位。
- `stoi/stod` 等轉換錯誤缺乏結構化容錯，資料異常時可能中斷流程。
- 存檔流程為直接覆寫，若中途中斷有機會留下不完整檔案。

基於前述風險，本次變更聚焦於「資料格式與持久化可靠性」升級，並明確要求資料解析與序列化以 STL 容器為核心建模。

## 變更內容

- 導入 **STL 容器導向** 的結構化文字格式（Key-Value Record），取代脆弱的逗號位置依賴。
- 規範三種資料檔（inventory/accounts/rental_records）的欄位鍵名與版本標記。
- 不提供舊 CSV 格式相容路徑：系統僅接受 `kv-v1`。
- 新增持久化可靠性要求：使用暫存檔 + rename 的原子寫入流程。
- 新增解析容錯要求：單筆資料錯誤時記錄並跳過，不得造成整體載入失敗。
- 新增帳戶安全要求：密碼不得明文儲存或回顯，必須以雜湊（含鹽）保存與驗證。
- 新增架構重整要求：拆分 `LibrarySystem` 的 UI、應用服務、資料存取職責。
- 新增文件治理要求：所有功能/架構/安全變更都必須同步更新對應文件。
- 新增文件同步機制（Doc Sync Gate）：未更新對應文件的變更不可視為完成。

## 能力範圍

### 新增能力
- `stl-structured-persistence`: 定義並規範以 `std::vector`、`std::unordered_map`、`std::optional` 等 STL 類別支撐的資料格式與讀寫策略。
- `library-system-architecture`: 定義 `LibrarySystem` 職責拆分邊界與依賴方向。
- `documentation-governance`: 定義文件覆蓋範圍、同步更新責任與文件同步門檻機制。

### 調整能力
- `media-rental-system`: 媒體資料序列化格式改為具欄位鍵名的結構化表示。
- `account-management`: 帳戶資料序列化格式改為具欄位鍵名的結構化表示。
- `rental-history-records`: 租借紀錄資料格式與載入容錯機制升級。

## 影響範圍

- 影響資料存取層（load/save）與序列化函式設計。
- 需更新 `data/*.txt` 的格式規範與 README 說明。
- 需補充 `kv-v1` 嚴格格式驗證測試（不含舊格式回溯相容）。
- 影響帳戶驗證流程與資料欄位（密碼雜湊與鹽值）。
- 影響核心控制器設計：`LibrarySystem` 將改為協調者，不再承擔全部職責。
- 需新增文件同步檢查流程（變更清單與自動化檢查），避免實作與文件脫節。

## 實作完成狀態（2026-06-04）

- 已導入 `kv-v1` 嚴格標頭驗證、必要鍵檢查、錯誤診斷輸出與值轉義策略。
- 已完成多檔寫入失敗回滾保護（`.bak` 還原路徑）。
- 已完成 `LibrarySystem` 職責收斂，拆分 `MenuRenderer` / `LibraryMenus` / `LibraryService` / `LibraryOperations` / `LibraryViews`。
- 已新增 `scripts/run-kv-tests.ps1`、`scripts/check-doc-sync.ps1` 與 CI Doc Sync Gate workflow。
- 已補齊 `docs/` 專案層文件與對應 capability specs。
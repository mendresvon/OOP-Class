## 背景脈絡

本變更採「低風險漸進升級」：先解決資料格式與持久化可靠性，避免一次性大改整體架構。核心目標是讓資料模型與格式映射更明確，並以 STL 類別作為解析中介表示。

## 目標 / 非目標

**目標**
- 定義可擴充、欄位順序無關的文字持久化格式。
- 解析邏輯以 STL 容器建模，降低硬編碼索引與格式脆弱性。
- 寫入流程具備原子性與容錯。
- 解決帳戶密碼明文風險，改為雜湊驗證。
- 解決 `LibrarySystem` 職責過重，完成 UI/Service/Repository 拆分。
- 建立文件同步機制，確保變更與文件一致。

**非目標**
- 不導入外部資料庫（SQLite/MySQL）。
- 不更動核心借還業務規則（費率、角色功能）。

## 資料格式設計決策

### 1) Record 表示法
每筆資料採單行 Key-Value：
- 欄位分隔：`|`
- 鍵值分隔：`=`
- 範例：`type=BOOK|id=B001|title=C++ Primer|borrowed=0|author=Lippman|isbn=...|status=ACTIVE`

### 2) STL 中介模型
- `using FieldMap = std::unordered_map<std::string, std::string>;`
- `using RecordList = std::vector<FieldMap>;`
- 可選欄位以 `std::optional<T>` 映射（例如 `returnDate`、`adminLevel`）。

### 3) 版本欄位
每個檔案首行使用註記：
- `# format=kv-v1`

### 4) 帳戶安全欄位
帳戶記錄改為：
- `passwordHash=<hex/base64>`
- `passwordSalt=<hex/base64>`

不得輸出或儲存 `password` 明文欄位。

## 架構重整決策

為降低耦合與提高可測試性，`LibrarySystem` 改為協調層，職責分為：
- `MenuRenderer`：CLI 顯示與互動輸入。
- `LibraryService`：借還、搜尋、管理等業務規則。
- `PersistenceRepository`：`kv-v1` 讀寫、原子寫入、解析容錯。

依賴方向：`MenuRenderer -> LibraryService -> PersistenceRepository`。

## 文件同步機制

### 1) 文件覆蓋矩陣
每次功能變更需對照以下文件至少一項更新：
- 使用者行為/操作改變：`README.md`
- 資料格式或欄位改變：`README.md` + 對應 capability spec
- 架構邊界改變：change `design.md` + `library-system-architecture` spec
- 安全策略改變：`account-management` spec + README 安全章節

### 2) 完成定義強制條件
任一任務標記完成前，必須同時滿足：
1. 程式實作完成
2. 對應文件已更新
3. 文件同步檢查通過

### 3) Doc Sync Gate
建立自動化檢查（例如 `scripts/check-doc-sync` 或 CI job）：
- 若變更觸及 `*.cpp`/`*.h`/`data/*.txt`，且未包含文件變更（README 或 openspec 相關檔案），則檢查失敗。
- 若變更觸及安全/資料格式關鍵模組，要求對應 spec 檔案必須同時變更。

## 載入 / 儲存策略

### 載入
1. 先判斷檔案版本標記。
2. 若為 `kv-v1`：解析為 `FieldMap`，再映射為 domain 物件。
3. 若缺少版本標頭或格式不符：視為格式錯誤並回報。
4. 單筆資料欄位缺失或型別錯誤：記錄錯誤並跳過該筆，不中止整體載入。

### 儲存
1. 先將 domain 物件轉為 `FieldMap`。
2. 輸出到 `*.tmp` 暫存檔。
3. flush/close 成功後 rename 取代正式檔。
4. 任一檔案失敗時保留舊檔，回報錯誤訊息。

## 風險 / 取捨

- 權衡：不提供舊格式相容會提高切換門檻。
- 緩解：提供一次性轉檔工具與清楚錯誤訊息，協助資料修復。

- 權衡：`std::unordered_map` 無序，輸出欄位順序需額外控制。
- 緩解：輸出時使用預定義 key order（`std::vector<std::string>`）產生穩定結果。

- 權衡：模組拆分增加初期檔案與介面數量。
- 緩解：明確定義介面契約，先以最小切分交付再迭代優化。

- 權衡：文件同步門檻會增加每次變更成本。
- 緩解：以檢查腳本與模板降低人工比對成本，讓流程固定化。

## 驗證計畫

- 標題含逗號、管線符號等邊界值可穩定處理（需轉義策略測試）。
- 模擬部分壞資料，驗證系統可啟動且跳過錯誤行。
- 寫檔中斷情境下，正式檔不應變成半套內容。
- 驗證帳戶檔案中不含明文密碼，且登入使用雜湊比對。
- 驗證 `LibrarySystem` 僅協調流程，不再直接持有主要解析與業務邏輯實作。
- 驗證程式變更若未同步更新文件會被 Doc Sync Gate 阻擋。

## 實作對照（2026-06-04）

- 轉義策略：`LibrarySystem.cpp` 中 `escapeValue`/`unescapeValue` 已實作 `\\`、`\|`、`\=`、`\n`、`\r`。
- 嚴格驗證：`validateHeader` 與 `hasRequiredKeys` 已實作缺標頭/缺鍵即回報。
- 診斷輸出：`reportParseIssue` 以 `[kv-v1] file:line - message` 形式輸出。
- 多檔回滾：`save()` 內新增 `.bak` 備份與失敗時還原。
- 文件與流程：已提供 `docs/` 文件、Doc Sync Gate 腳本、CI workflow 與 CMake target 整合。
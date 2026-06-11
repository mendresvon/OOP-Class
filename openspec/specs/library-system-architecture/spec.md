## 新增需求

### 需求：LibrarySystem 職責分離
系統必須重構 `LibrarySystem` 為分離職責的架構，避免將流程協調、業務邏輯與持久化實作集中於單一類別。

#### 情境：UI 與業務邏輯分離
- **當** 觸發任一選單操作
- **則** UI 顯示與輸入處理由 `MenuRenderer` 負責，業務操作由 `LibraryService` 執行。

#### 情境：持久化與協調流程隔離
- **當** 執行資料載入或儲存
- **則** 持久化解析與檔案 I/O 必須由 `PersistenceRepository` 負責，而 `LibrarySystem` 僅做流程協調。

### 需求：依賴方向約束
系統必須強制採用單向依賴：UI -> Service -> Repository。

#### 情境：防止 UI 流程直接寫檔
- **當** 使用者或管理者操作需要更新資料
- **則** 必須透過定義好的介面呼叫 service 與 repository，不得在選單控制程式中直接寫檔。

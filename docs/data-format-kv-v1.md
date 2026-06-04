# kv-v1 資料格式規範

## 檔案標頭

每個資料檔第一行必須包含：

`# format=kv-v1`

## 記錄格式

- 欄位分隔：`|`
- 鍵值分隔：`=`
- 單行一筆記錄

## 值轉義規則（Task 1.2）

- `\\`：表示反斜線
- `\|`：表示 `|`
- `\=`：表示 `=`
- `\n`：表示換行
- `\r`：表示 CR

空值策略：

- 允許空字串（例如 `borrowed=`）
- 必要鍵若缺失或值為空，該筆記錄視為無效並跳過

範例：

`type=BOOK|id=B001|title=C++ Primer|borrowed=0|author=Lippman|isbn=9780321714114|status=ACTIVE`

## 解析中介模型（STL）

- `FieldMap = std::unordered_map<std::string, std::string>`
- `RecordList = std::vector<FieldMap>`
- 可選欄位使用 `std::optional<T>` 映射

## 驗證規則

1. 缺少格式標頭：視為格式錯誤。
2. 缺必要鍵名：該筆記錄跳過並記錄錯誤。
3. 型別轉換失敗：記錄錯誤，該欄位採容錯預設值。
4. 解析錯誤輸出：以 `[kv-v1] <file>:<line> - <message> | <rawLine>` 形式輸出。

## 儲存規則

1. 先寫入暫存檔（`.tmp`）。
2. 寫入成功後原子替換正式檔。
3. 多檔寫入失敗時，嘗試由 `.bak` 還原已改寫檔案。

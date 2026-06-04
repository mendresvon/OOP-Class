# 智慧型圖書/影音多媒體租借管理系統

本專案使用 C++17 開發，提供角色分流選單、借還流程、交易紀錄、回收桶管理，以及以 `kv-v1` 為核心的檔案持久化。

## 專案架構重點

- 流程協調：`LibrarySystem`
- 選單互動：`MenuRenderer`、`LibraryMenus`
- 業務邏輯：`LibraryService`、`LibraryOperations`
- 查詢與報表：`LibraryViews`
- 檔案存取：`PersistenceRepository`（位於 `LibrarySystem.cpp`）
- 領域模型：`media/*`、`accounts/*`、`RentalRecord.h`

## 資料格式與安全

- 三個資料檔必須是 `kv-v1`：`data/inventory.txt`、`data/accounts.txt`、`data/rental_records.txt`
- 每檔首行必須為 `# format=kv-v1`
- 欄位分隔使用 `|`，鍵值分隔使用 `=`
- 值支援跳脫字元：`\\`、`\|`、`\=`、`\n`、`\r`
- 帳號資料僅允許 `passwordHash`、`passwordSalt`，不得出現 `password=` 明文欄位

## 建置方式

### CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 直接使用 g++（Windows / MinGW）

```bash
g++ -std=c++17 -Wall main.cpp LibrarySystem.cpp LibraryService.cpp MenuRenderer.cpp LibraryOperations.cpp LibraryViews.cpp LibraryMenus.cpp media/MediaItem.cpp media/Book.cpp media/Dvd.cpp media/Magazine.cpp accounts/Account.cpp accounts/User.cpp accounts/Admin.cpp -o SmartLibrarySystem.exe
```

## 驗證與文件治理

### 執行 kv-v1 測試

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\run-kv-tests.ps1
```

### 執行 Doc Sync Gate

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\check-doc-sync.ps1
```

### CMake 驗證目標

- `doc_sync_gate`
- `run_kv_tests`

## 文件入口

- [docs/README.md](docs/README.md)
- [docs/project-overview.md](docs/project-overview.md)
- [docs/architecture.md](docs/architecture.md)
- [docs/data-format-kv-v1.md](docs/data-format-kv-v1.md)
- [docs/security-authentication.md](docs/security-authentication.md)
- [docs/testing-validation.md](docs/testing-validation.md)
- [docs/changelog.md](docs/changelog.md)

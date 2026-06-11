# 安全與驗證

## 密碼政策

- 禁止明文儲存密碼
- 禁止在管理頁或日誌顯示明文密碼
- 使用 `passwordHash` + `passwordSalt` 儲存憑證
- 註冊時由 `Account::generateSalt()` 產生鹽值，並以 `Account::computePasswordHash()` 計算雜湊

## 登入驗證

1. 依帳號讀取 `passwordSalt`
2. 使用輸入密碼 + salt 計算 hash
3. 與 `passwordHash` 比對
4. 成功才允許登入

> 目前雜湊採 FNV-1a（非密碼學等級），用途為避免明文落地。若上線到高安全場景，應升級為專用 KDF（如 Argon2、scrypt、bcrypt）。

## 資料檔欄位

帳戶記錄應至少包含：

- `username`
- `role`
- `passwordHash`
- `passwordSalt`

## 安全檢查清單

- 檔案中不得存在 `password=` 明文欄位
- 程式輸出不得顯示原始密碼
- 變更驗證邏輯時需同步更新 OpenSpec 規格與本文件
- 執行 `scripts/run-kv-tests.ps1` 的 credential 測試需通過

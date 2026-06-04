param(
    [string]$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")),
    [switch]$BuildBeforeRun = $true
)

$ErrorActionPreference = "Stop"

function Copy-TestData([string]$sourceDir, [string]$targetDir) {
    New-Item -ItemType Directory -Force -Path $targetDir | Out-Null
    Copy-Item -Force (Join-Path $sourceDir "inventory.txt") (Join-Path $targetDir "inventory.txt")
    Copy-Item -Force (Join-Path $sourceDir "accounts.txt") (Join-Path $targetDir "accounts.txt")
    Copy-Item -Force (Join-Path $sourceDir "rental_records.txt") (Join-Path $targetDir "rental_records.txt")
}

function Assert-Contains([string]$text, [string]$expected, [string]$message) {
    if (-not $text.Contains($expected)) {
        throw "[FAIL] $message`nExpected to find: $expected`nActual: $text"
    }
}

Push-Location $RepoRoot
try {
    $exePath = Join-Path $RepoRoot "SmartLibrarySystem.exe"
    if ($BuildBeforeRun -or -not (Test-Path $exePath)) {
        & "C:\MinGW\bin\g++.exe" -std=c++17 -Wall `
            main.cpp LibrarySystem.cpp LibraryService.cpp MenuRenderer.cpp LibraryOperations.cpp LibraryViews.cpp LibraryMenus.cpp `
            media/MediaItem.cpp media/Book.cpp media/Dvd.cpp media/Magazine.cpp `
            accounts/Account.cpp accounts/User.cpp accounts/Admin.cpp `
            -o SmartLibrarySystem.exe
        if ($LASTEXITCODE -ne 0) {
            throw "[FAIL] Build failed"
        }
    }

    $tmpRoot = Join-Path $RepoRoot "build\test-sandbox"
    if (Test-Path $tmpRoot) {
        Remove-Item -Recurse -Force $tmpRoot
    }
    New-Item -ItemType Directory -Force -Path $tmpRoot | Out-Null

    $strictRoot = Join-Path $tmpRoot "strict-invalid-header"
    New-Item -ItemType Directory -Force -Path (Join-Path $strictRoot "data") | Out-Null
    Copy-Item -Force $exePath (Join-Path $strictRoot "SmartLibrarySystem.exe")
    Copy-TestData (Join-Path $RepoRoot "tests\fixtures\strict-invalid-header\data") (Join-Path $strictRoot "data")

    Push-Location $strictRoot
    try {
        $prevErrAction = $ErrorActionPreference
        $ErrorActionPreference = "Continue"
        $strictOutput = (cmd /c "echo 3|SmartLibrarySystem.exe" 2>&1 | Out-String)
        $ErrorActionPreference = $prevErrAction
    }
    finally {
        $ErrorActionPreference = "Stop"
        Pop-Location
    }
    Assert-Contains $strictOutput "kv-v1" "Strict header validation should reject invalid format header"

    $tolerantRoot = Join-Path $tmpRoot "tolerant-bad-lines"
    New-Item -ItemType Directory -Force -Path (Join-Path $tolerantRoot "data") | Out-Null
    Copy-Item -Force $exePath (Join-Path $tolerantRoot "SmartLibrarySystem.exe")
    Copy-TestData (Join-Path $RepoRoot "tests\fixtures\tolerant-bad-lines\data") (Join-Path $tolerantRoot "data")

    Push-Location $tolerantRoot
    try {
        $prevErrAction = $ErrorActionPreference
        $ErrorActionPreference = "Continue"
        $tolerantOutput = (cmd /c "echo 3|SmartLibrarySystem.exe" 2>&1 | Out-String)
        $ErrorActionPreference = $prevErrAction
    }
    finally {
        $ErrorActionPreference = "Stop"
        Pop-Location
    }
    Assert-Contains $tolerantOutput "(v1.0)" "Corrupted lines should be tolerated and app should still start"
    Assert-Contains $tolerantOutput "[kv-v1]" "Corrupted lines should emit kv-v1 diagnostics"

    $accountsText = Get-Content (Join-Path $RepoRoot "data\accounts.txt") -Raw
    if ($accountsText -match "(^|\|)password=") {
        throw "[FAIL] Plain password field detected in data/accounts.txt"
    }
    Assert-Contains $accountsText "passwordHash=" "Accounts should include passwordHash field"
    Assert-Contains $accountsText "passwordSalt=" "Accounts should include passwordSalt field"

    Write-Host "[PASS] kv-v1 strict validation tests"
    Write-Host "[PASS] corrupted line tolerance tests"
    Write-Host "[PASS] credential persistence safety tests"
}
finally {
    Pop-Location
}

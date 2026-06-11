param(
    [string]$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")),
    [string]$BaseRef = ""
)

$ErrorActionPreference = "Stop"
Push-Location $RepoRoot
try {
    $docPatterns = @(
        "README.md",
        "docs/",
        "openspec/"
    )

    $codePatterns = @(
        "*.cpp",
        "*.h",
        "data/"
    )

    if ([string]::IsNullOrWhiteSpace($BaseRef)) {
        $changed = git diff --name-only
        $staged = git diff --name-only --cached
        $untracked = git ls-files --others --exclude-standard
        $changedFiles = @($changed + $staged + $untracked | Where-Object { -not [string]::IsNullOrWhiteSpace($_) } | Sort-Object -Unique)
    } else {
        $changedFiles = @(git diff --name-only $BaseRef...HEAD | Where-Object { -not [string]::IsNullOrWhiteSpace($_) })
    }

    $normalizedChangedFiles = @()
    foreach ($f in $changedFiles) {
        $normalizedChangedFiles += $f.Replace('\\', '/')
    }

    if ($changedFiles.Count -eq 0) {
        Write-Host "Doc Sync Gate: no changed files, skip"
        exit 0
    }

    $hasCodeChange = $false
    $hasDocChange = $false
    $touchesFormatOrSecurity = $false
    $touchesArchitecture = $false

    foreach ($normalized in $normalizedChangedFiles) {

        if ($normalized -like "*.cpp" -or $normalized -like "*.h" -or $normalized.StartsWith("data/")) {
            $hasCodeChange = $true
        }

        if ($normalized -eq "README.md" -or $normalized.StartsWith("docs/") -or $normalized.StartsWith("openspec/")) {
            $hasDocChange = $true
        }

        if ($normalized -match "LibrarySystem|LibraryService|Account|accounts/|data/|LibraryOperations|LibraryViews|LibraryMenus") {
            $touchesFormatOrSecurity = $true
        }

        if ($normalized -match "LibrarySystem|MenuRenderer|LibraryService|LibraryOperations|LibraryViews|LibraryMenus") {
            $touchesArchitecture = $true
        }
    }

    if ($hasCodeChange -and -not $hasDocChange) {
        Write-Error "Doc Sync Gate failed: code/data changed but no docs updated (README.md/docs/openspec)."
    }

    if ($touchesFormatOrSecurity) {
        $requiredGroups = @(
            @("README.md", "docs/data-format-kv-v1.md"),
            @("docs/security-authentication.md", "openspec/specs/account-management/spec.md"),
            @("openspec/specs/rental-history-records/spec.md", "openspec/specs/stl-structured-persistence/spec.md")
        )

        foreach ($group in $requiredGroups) {
            $matched = $false
            foreach ($candidate in $group) {
                if ($normalizedChangedFiles -contains $candidate) {
                    $matched = $true
                    break
                }
            }
            if (-not $matched) {
                Write-Error "Doc Sync Gate failed: format/security related change requires one of: $($group -join ', ')"
            }
        }
    }

    if ($touchesArchitecture) {
        $requiredGroups = @(
            @("docs/architecture.md", "openspec/specs/library-system-architecture/spec.md"),
            @("openspec/specs/media-rental-system/spec.md")
        )

        foreach ($group in $requiredGroups) {
            $matched = $false
            foreach ($candidate in $group) {
                if ($normalizedChangedFiles -contains $candidate) {
                    $matched = $true
                    break
                }
            }
            if (-not $matched) {
                Write-Error "Doc Sync Gate failed: architecture related change requires one of: $($group -join ', ')"
            }
        }
    }

    Write-Host "Doc Sync Gate passed"
    exit 0
}
finally {
    Pop-Location
}

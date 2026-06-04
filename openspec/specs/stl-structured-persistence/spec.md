# stl-structured-persistence Specification

## Purpose
Define the `kv-v1` structured persistence format and strict parser behavior for `inventory.txt`, `accounts.txt`, and `rental_records.txt`.

## Requirements
### Requirement: kv-v1 Header and Required Keys
The system SHALL reject files that do not start with `# format=kv-v1`. For every record line, required keys MUST be present according to record type.

#### Scenario: Missing format header
- **WHEN** any persistence file does not contain `# format=kv-v1` at the first non-empty line
- **THEN** startup SHALL fail with a visible error message.

#### Scenario: Missing required key in a record
- **WHEN** a record is parsed but required keys are missing
- **THEN** the parser SHALL emit diagnostic output and skip that record.

### Requirement: Escaped kv-v1 Values
The system SHALL support escaped value content to preserve separators and line breaks in fields.

#### Scenario: Record contains separators in title
- **WHEN** a title contains `|`, `=`, or newline
- **THEN** the value SHALL be written with escapes and restored during parsing.

### Requirement: Parser Fault Tolerance
The system SHALL continue loading valid records when malformed records are encountered.

#### Scenario: Broken line mixed with valid lines
- **WHEN** parser encounters malformed key-value syntax on one line
- **THEN** it SHALL emit diagnostics, skip the line, and continue loading subsequent valid records.

### Requirement: Multi-file Save Rollback
The system SHALL attempt rollback of already written files when a later file write fails in the same save operation.

#### Scenario: Mid-save failure while writing accounts or rental logs
- **WHEN** inventory write succeeds but a later file write fails
- **THEN** the repository SHALL restore previous file contents from backup snapshots.

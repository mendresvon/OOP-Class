# rental-history-records Specification

## Purpose
Define rental transaction recording and persistence behavior for borrow/return lifecycle.
## Requirements
### Requirement: Rent and Return Transaction Log
The system SHALL create a `RentalRecord` whenever a media item is borrowed or returned. The record MUST log transaction details, timestamps, calculated fees, and status (BORROWED, RETURNED, OVERDUE).

#### Scenario: User returns item and system computes fee
- **WHEN** user returns a media item after 5 days
- **THEN** the system SHALL calculate the rental fee using the media's polymorphic `getFee` implementation, update the record state to `RETURNED`, and set the return date.

### Requirement: Rental Persistence
The system SHALL persist all accounts, inventory items, and rental logs to physical text files (`accounts.txt`, `inventory.txt`, `rental_records.txt`) immediately upon state changes.

#### Scenario: File reloading on launch
- **WHEN** the application starts up
- **THEN** it SHALL parse and load all state from the persistent files on the hard drive into memory, reconstructing the accurate status of all active rentals.

### Requirement: kv-v1 Parser Tolerance
The system SHALL continue loading valid records when malformed record lines are encountered, while emitting diagnostics.

#### Scenario: Corrupted rental line
- **WHEN** a rental record line has invalid key-value format or invalid numeric fields
- **THEN** the parser SHALL emit diagnostics and skip or default that record field without crashing startup.


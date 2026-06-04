# recycle-bin-persistence Specification

## Purpose
Define recycle-bin archive lifecycle and persistent cleanup behavior for archived media items.
## Requirements
### Requirement: Recycle Bin Management and Hard Purge
The system SHALL support restoring archived media items back to `ACTIVE` status or performing a hard purge that permanently removes all archived (`ARCHIVED`) items from the single inventory vector and overwrites the text database.

#### Scenario: Admin empties the Recycle Bin
- **WHEN** the administrator selects "Empty Recycle Bin" and confirms the operation
- **THEN** the system SHALL remove all items with status `ARCHIVED` from the inventory memory, erase them from `inventory.txt`, and free their allocated memory.


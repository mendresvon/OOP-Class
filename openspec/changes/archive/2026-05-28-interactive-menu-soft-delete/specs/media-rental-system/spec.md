## MODIFIED Requirements

### Requirement: Add and Remove Media Items
The system SHALL allow administrators to add new media items to the inventory or remove existing ones. Removing an item SHALL NOT physically delete it immediately; instead, it MUST be soft-deleted and placed in the Recycle Bin by setting its status tag to `ARCHIVED`.

#### Scenario: Administrator soft deletes a Book
- **WHEN** administrator selects a book to delete using the keyboard arrow select menu
- **THEN** the system SHALL set the book's status to `ARCHIVED`, immediately saving this change to the inventory file, and making it invisible to regular user search and borrow workflows.

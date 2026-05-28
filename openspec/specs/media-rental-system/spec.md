# media-rental-system Specification

## Purpose
TBD - created by archiving change smart-media-rental-system. Update Purpose after archive.
## Requirements
### Requirement: Polymorphic Media Representation
The system SHALL model media items as polymorphic objects through a base class `MediaItem` and three derived classes: `Book`, `Dvd`, and `Magazine`. Each concrete class MUST provide its own implementation of the virtual `getFee` function and `serialize` function.

#### Scenario: Displaying item specific attributes
- **WHEN** the system displays inventory items
- **THEN** Books SHALL display ISBN and author, DVDs SHALL display director and duration, and Magazines SHALL display issue number and month.

### Requirement: Media Lookup and Filtering
The system SHALL allow users and administrators to search for media items by unique ID, keyword in title, or class category (Book, DVD, Magazine).

#### Scenario: Searching media by keyword
- **WHEN** user inputs a search keyword that matches a portion of the media title
- **THEN** the system SHALL output a filtered list of all matching media items.

### Requirement: Add and Remove Media Items
The system SHALL allow administrators to add new media items to the inventory or remove existing ones by their unique ID.

#### Scenario: Administrator adds a new Book
- **WHEN** administrator inputs new book attributes including unique ID, title, author, and ISBN
- **THEN** the system SHALL create the Book instance, add it to the inventory vector, and mark its initial status as not borrowed.


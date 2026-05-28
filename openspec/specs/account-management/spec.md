# account-management Specification

## Purpose
TBD - created by archiving change smart-media-rental-system. Update Purpose after archive.
## Requirements
### Requirement: User Registration and Login
The system SHALL support user registration and authentication. Users must supply a unique username and password to log in.

#### Scenario: Successful login
- **WHEN** user inputs a valid registered username and password
- **THEN** the system SHALL set `currentUser` to point to the active account and display the appropriate role-based menu.

### Requirement: Role-Based Interface Access Control
The system SHALL bifurcate user workflows based on their account role (User vs Admin). Users can borrow and return, whereas Admins can manage inventory and view system logs.

#### Scenario: Admin accesses admin menu
- **WHEN** an authenticated administrator logs in
- **THEN** the system SHALL show the Admin dashboard options and block general user rent/return workflows from execution.


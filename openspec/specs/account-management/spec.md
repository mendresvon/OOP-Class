# account-management Specification

## Purpose
Define registration, authentication, role dispatch, and credential persistence policy for user/admin accounts.
## Requirements
### Requirement: User Registration and Login
The system SHALL support user registration and authentication. Users must supply a unique username and password to log in.

#### Scenario: Successful login
- **WHEN** user inputs a valid registered username and password
- **THEN** the system SHALL set `currentUser` to point to the active account and display the appropriate role-based menu.

### Requirement: No Plaintext Password Persistence
The system SHALL persist account credentials as `passwordHash` and `passwordSalt` only, and SHALL NOT persist plaintext password fields.

#### Scenario: Saving account records
- **WHEN** account data is written to `accounts.txt`
- **THEN** each record SHALL contain `passwordHash` and `passwordSalt`, and SHALL NOT contain `password=`.

### Requirement: Role-Based Interface Access Control
The system SHALL bifurcate user workflows based on their account role (User vs Admin). Users can borrow and return, whereas Admins can manage inventory, view system logs, and access the "Recycle Bin and Archive Management" center. All menu selections MUST be driven by keyboard arrow keys with reverse video highlighting for the active item.

#### Scenario: Admin accesses admin menu and Recycle Bin submenu
- **WHEN** an authenticated administrator logs in
- **THEN** the system SHALL show the Admin dashboard driven by arrow key selections, featuring a sub-menu option for the Recycle Bin and Archive Management center.


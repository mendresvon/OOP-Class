## MODIFIED Requirements

### Requirement: Role-Based Interface Access Control
The system SHALL bifurcate user workflows based on their account role (User vs Admin). Users can borrow and return, whereas Admins can manage inventory, view system logs, and access the "Recycle Bin and Archive Management" center. All menu selections MUST be driven by keyboard arrow keys with reverse video highlighting for the active item.

#### Scenario: Admin accesses admin menu and Recycle Bin submenu
- **WHEN** an authenticated administrator logs in
- **THEN** the system SHALL show the Admin dashboard driven by arrow key selections, featuring a sub-menu option for the Recycle Bin and Archive Management center.

# library-system-architecture Specification

## Purpose
Define the responsibility boundaries so `LibrarySystem` stays as an application coordinator and delegates UI, workflows, and views to dedicated modules.

## Requirements
### Requirement: Coordinator-Only LibrarySystem
`LibrarySystem` SHALL only coordinate startup, authentication flow orchestration, and repository save/load invocation.

#### Scenario: User opens role menu
- **WHEN** an authenticated user enters menu flow
- **THEN** the logic SHALL be delegated to dedicated menu/view/operation components, not implemented inline in `LibrarySystem`.

### Requirement: Dedicated Workflow Modules
The system SHALL split responsibilities across dedicated modules.

#### Scenario: Borrow and return operations
- **WHEN** borrow or return is triggered
- **THEN** business logic SHALL execute in `LibraryOperations`.

#### Scenario: Inventory and report display
- **WHEN** inventory list or reports are requested
- **THEN** rendering and query output SHALL execute in `LibraryViews`.

#### Scenario: Role menu loops
- **WHEN** account menu dispatch is invoked
- **THEN** role menu loop SHALL execute in `LibraryMenus`.

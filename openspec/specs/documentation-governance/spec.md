# documentation-governance Specification

## Purpose
Ensure all architecture, data-format, and security changes are shipped with synchronized documentation updates.

## Requirements
### Requirement: Documentation Coverage Matrix
The project SHALL maintain a document coverage matrix mapping change categories to required documents.

#### Scenario: Data format update
- **WHEN** persistence format behavior changes
- **THEN** `docs/data-format-kv-v1.md`, `README.md`, and related OpenSpec specs SHALL be updated together.

### Requirement: Doc Sync Gate Enforcement
The project SHALL provide an automated Doc Sync Gate check in local workflow and CI.

#### Scenario: Code changed without docs
- **WHEN** `.cpp`/`.h`/`data/` files change but required docs are unchanged
- **THEN** Doc Sync Gate SHALL fail.

### Requirement: Definition of Done Includes Docs
Task completion SHALL require a documentation checklist pass.

#### Scenario: Marking implementation complete
- **WHEN** a change is ready to close
- **THEN** DoD checklist MUST confirm implementation, tests, and required docs are all updated.

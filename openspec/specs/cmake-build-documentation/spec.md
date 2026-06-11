# cmake-build-documentation Specification

## Purpose
TBD - created by archiving change smart-media-rental-system. Update Purpose after archive.
## Requirements
### Requirement: CMake Out-of-Source Build
The system SHALL compile successfully using CMake with standard out-of-source compilation patterns.

#### Scenario: Compiling project inside build directory
- **WHEN** developer runs `cmake ..` and `cmake --build .` from a separate build folder
- **THEN** the project SHALL compile without warnings and output the executable target `SmartLibrarySystem`.

### Requirement: Automated Testing Resource Copying
The build system SHALL automatically copy the initial mock data directory (`data/`) to the output build target binary folder during cmake configuration or build phase.

#### Scenario: Launching binary directly from build dir
- **WHEN** the user executes the built binary directly inside the build directory
- **THEN** the system SHALL load configuration files successfully from the local `data/` folder without path failure errors.


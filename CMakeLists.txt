cmake_minimum_required(VERSION 3.15)
project(SmartLibrarySystem VERSION 1.0 LANGUAGES CXX)

# Require C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Recurse glob source and header files
file(GLOB_RECURSE SOURCES 
    "main.cpp"
    "LibrarySystem.cpp"
    "LibraryService.cpp"
    "MenuRenderer.cpp"
    "LibraryOperations.cpp"
    "LibraryViews.cpp"
    "LibraryMenus.cpp"
    "media/*.cpp"
    "accounts/*.cpp"
)

file(GLOB_RECURSE HEADERS 
    "LibrarySystem.h"
    "LibraryService.h"
    "MenuRenderer.h"
    "LibraryOperations.h"
    "LibraryViews.h"
    "LibraryMenus.h"
    "media/*.h"
    "accounts/*.h"
)

# Build Target
add_executable(SmartLibrarySystem ${SOURCES} ${HEADERS})

# Automatically copy data/ directory to CMAKE_CURRENT_BINARY_DIR so paths work properly out-of-source
add_custom_target(copy_data_files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/data"
    "${CMAKE_CURRENT_BINARY_DIR}/data"
    COMMENT "Copying data files to build directory..."
)
add_dependencies(SmartLibrarySystem copy_data_files)

if (WIN32)
    add_custom_target(doc_sync_gate
        COMMAND powershell -ExecutionPolicy Bypass -File "${CMAKE_CURRENT_SOURCE_DIR}/scripts/check-doc-sync.ps1"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Running Doc Sync Gate..."
    )

    add_custom_target(run_kv_tests
        COMMAND powershell -ExecutionPolicy Bypass -File "${CMAKE_CURRENT_SOURCE_DIR}/scripts/run-kv-tests.ps1"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Running kv-v1 validation tests..."
    )
endif()

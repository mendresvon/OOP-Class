#ifndef LIBRARY_OPERATIONS_H
#define LIBRARY_OPERATIONS_H

class LibrarySystem;

class LibraryOperations {
public:
    static void executeBorrow(LibrarySystem& system);
    static void executeReturn(LibrarySystem& system);
    static void adminAddMedia(LibrarySystem& system);
    static void adminRemoveMedia(LibrarySystem& system);
    static void adminRecycleBinMenu(LibrarySystem& system);
};

#endif

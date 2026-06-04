#ifndef LIBRARY_VIEWS_H
#define LIBRARY_VIEWS_H

class LibrarySystem;

class LibraryViews {
public:
    static void showInventory(const LibrarySystem& system);
    static void searchInventory(const LibrarySystem& system);
    static void showUserRentalHistory(const LibrarySystem& system);
    static void adminViewAllAccounts(const LibrarySystem& system);
    static void adminViewAllRecords(const LibrarySystem& system);
};

#endif

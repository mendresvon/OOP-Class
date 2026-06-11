#ifndef LIBRARY_MENUS_H
#define LIBRARY_MENUS_H

class LibrarySystem;

class LibraryMenus {
public:
    static void runUserMenu(LibrarySystem& system);
    static void runAdminMenu(LibrarySystem& system);
};

#endif

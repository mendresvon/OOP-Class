#include "LibrarySystem.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    LibrarySystem system;
    system.run();
    return 0;
}


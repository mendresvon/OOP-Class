#include "MenuRenderer.h"

#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#endif

namespace {
bool enableAnsiColors() {
#ifdef _WIN32
    constexpr DWORD kEnableVirtualTerminalProcessing = 0x0004;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) {
        return false;
    }

    mode |= kEnableVirtualTerminalProcessing;
    if (!SetConsoleMode(hOut, mode)) {
        return false;
    }
#endif
    return true;
}
}

namespace MenuRenderer {

void initialize() {
    enableAnsiColors();
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void pause() {
    std::cout << "\n按 Enter 繼續...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

std::string getMaskedPassword() {
    std::string password;
#ifdef _WIN32
    char ch = 0;
    while ((ch = static_cast<char>(_getch())) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
            }
        } else if (ch >= 32) {
            password.push_back(ch);
        }
    }
#else
    std::getline(std::cin, password);
#endif
    std::cout << '\n';
    return password;
}

int getMenuSelection(const std::vector<std::string>& options, const std::string& title) {
    while (true) {
        clearScreen();
        std::cout << title << "\n";
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << "  " << (i + 1) << ". " << options[i] << "\n";
        }
        std::cout << "請輸入選項 (1-" << options.size() << "): ";
        std::string choice;
        std::getline(std::cin, choice);
        try {
            int selection = std::stoi(choice) - 1;
            if (selection >= 0 && selection < static_cast<int>(options.size())) {
                return selection;
            }
        } catch (...) {
        }
        std::cout << "無效輸入，請重新選擇。\n";
        pause();
    }
}

}
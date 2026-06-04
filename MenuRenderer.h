#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H

#include <string>
#include <vector>

namespace MenuRenderer {
void initialize();
void clearScreen();
void pause();
std::string getMaskedPassword();
int getMenuSelection(const std::vector<std::string>& options, const std::string& title);
}

#endif
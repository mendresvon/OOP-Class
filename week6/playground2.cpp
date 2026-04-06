// demo_swap_compare.cpp
#include <iostream>
using namespace std;


// ── 1. Call by Value (does NOT work for swap) ─────────────────
void swapValue(int a, int b) {
    int temp = a; a = b; b = temp;
    // changes are local only — caller sees nothing
}


// ── 2. Call by Address ───────────────────────────────────────
void swapAddress(int* a, int* b) {
    int temp = *a; *a = *b; *b = temp;
}


// ── 3. Call by Reference ─────────────────────────────────────
void swapReference(int& a, int& b) {
    int temp = a; a = b; b = temp;
}


int main() {
    int x, y;


    x = 10; y = 20;
    swapValue(x, y);
    cout << "[Value]     x=" << x << " y=" << y << endl;  // 10 20 (no change)


    x = 10; y = 20;
    swapAddress(&x, &y);
    cout << "[Address]   x=" << x << " y=" << y << endl;  // 20 10


    x = 10; y = 20;
    swapReference(x, y);
    cout << "[Reference] x=" << x << " y=" << y << endl;  // 20 10


    return 0;
}


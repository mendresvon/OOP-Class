// demo_const_pointer.cpp
#include <iostream>
using namespace std;


int main() {
    int a = 10, b = 20;


    // 1. Pointer to const — cannot change *p, but can change p
    const int* p1 = &a;
    // *p1 = 99;       // ❌ compile error: read-only
    p1 = &b;            // ✅ fine: redirecting the pointer
    cout << "p1 → " << *p1 << endl;   // 20


    // 2. const pointer — can change *p2, but NOT p2 itself
    int* const p2 = &a;
    *p2 = 99;           // ✅ fine: modifying the value
    // p2 = &b;         // ❌ compile error: pointer is const
    cout << "a via p2 = " << *p2 << endl;   // 99


    // 3. const pointer to const — neither can change
    const int* const p3 = &b;
    cout << "p3 → " << *p3 << endl;   // 20


    return 0;
}


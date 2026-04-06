// demo_const_ref.cpp
#include <iostream>
#include <string>
using namespace std;


// ── By value: makes a full copy of the string every call ──────
void printByValue(string s) {
    cout << "[Value]  " << s << endl;
}


// ── By const reference: zero copy, read-only guarantee ─────────
void printByConstRef(const string& s) {
    // s += " modified";  // ❌ compile error — const ref is read-only
    cout << "[ConstRef] " << s << endl;
}


// ── Non-const reference: can modify the caller's variable ──────
void appendExclaim(string& s) {
    s += "!";   // modifies the caller's string
}


int main() {
    string greeting = "Hello, C++";


    printByValue(greeting);       // copy made
    printByConstRef(greeting);    // no copy, safe
    appendExclaim(greeting);      // modifies greeting
    cout << greeting << endl;     // Hello, C++!


    return 0;
}


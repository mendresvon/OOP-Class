#include <iostream>
#include <string>
using namespace std;

// string, string methods
int main() {
    // --- String initialization ---
    string str0(10, '*');
    string str1 = "Hello";
    string str2 = "World";
    string str3 = "Hello World!";
    string str3a = "Hello \\ World!";   // backslash escape
    string str3b = "Hello \\ World!";   // same

    cout << "str0 = " << str0 << endl;
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;
    cout << "str3:" << str3 << endl;
    cout << "str3a:" << str3a << endl;
    cout << "str3b:" << str3b << endl;

    // --- String capacity & size info ---
    cout << "str3 capacity = " << str3.capacity() << endl;
    cout << "str3 length(size) = " << str3.length() << endl;
    cout << "str3 max_size = " << str3.max_size() << endl;
    cout << "str3 size = " << str3.size() << endl;
    cout << "str3 empty = " << str3.empty() << endl;

    // --- Character access ---
    cout << "str3[0] = " << str3[0] << endl;
    cout << "str3.at(0) = " << str3.at(0) << endl;
    cout << "str3.at(4) = " << str3.at(4) << endl;
    cout << "str3.front() = " << str3.front() << endl;
    cout << "str3.back() = " << str3.back() << endl;

    return 0;
}

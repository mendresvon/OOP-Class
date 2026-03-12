#include <iostream>
#include <iomanip>    // needed for setprecision, fixed, setw
#include <typeinfo>   // needed for typeid().name()
#include <string>

using namespace std;

int main() {
    // Some variables to play around with
    int a = 100;
    double b = 3.14159265358979;
    auto str = "Hello C++";         // auto here gives us const char* (pointer to a C-style string)
    string stdStr = "Hello Modern"; // this is the proper C++ string object

    cout << "===== 1. Variable Types and Sizes =====" << endl;

    // Check what type and how much memory 'a' takes
    cout << "Variable a [int]:" << endl;
    cout << "  - Value: " << a << endl;
    cout << "  - Type: " << typeid(a).name() << endl;
    cout << "  - Size: " << sizeof(a) << " bytes" << endl << endl;

    // 'auto' just made 'str' a pointer, not a string object - notice the weird type name
    cout << "Variable str [auto -> const char*]:" << endl;
    cout << "  - Content: " << str << endl;
    cout << "  - Type: " << typeid(str).name() << " (PKc means: Pointer to Konst char)" << endl;
    cout << "  - Size: " << sizeof(str) << " bytes (pointers are always 8 bytes on 64-bit systems)" << endl << endl;

    // sizeof on a string object gives the object size, NOT how long the text inside is
    cout << "Variable stdStr [std::string]:" << endl;
    cout << "  - Size: " << sizeof(stdStr) << " bytes (this is the object itself, not the text length)" << endl << endl;

    cout << "===== 2. Controlling Decimal Precision =====" << endl;

    // By default, cout shows about 6 significant digits
    cout << "Default display of b: " << b << endl;

    // setprecision controls significant digits (without fixed)
    cout << "4 significant digits: " << setprecision(4) << b << endl;

    // fixed + setprecision = lock to exactly N digits after the decimal point
    cout << fixed << setprecision(2);
    cout << "Fixed 2 decimal places: " << b << endl;

    cout << fixed << setprecision(10);
    cout << "Fixed 10 decimal places: " << b << endl;

    // --- Making a simple table with setw ---
    cout << "\n===== 3. Table Formatting Demo =====" << endl;
    cout << setfill('-') << setw(30) << "-" << endl; // print a divider line
    cout << setfill(' ');                             // always reset fill back to space when done
    cout << left << setw(15) << "Item" << right << setw(15) << "Value" << endl;
    cout << left << setw(15) << "int a"    << right << setw(15) << a << endl;
    cout << left << setw(15) << "double b" << right << setw(15) << fixed << setprecision(2) << b << endl;

    return 0;
}
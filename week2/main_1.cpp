#include <iostream>
#include <iomanip>    // needed for setprecision, fixed, setw
#include <typeinfo>   // needed for typeid().name()
#include <string>     // for comparison with std::string

using namespace std;

int main() {
    // 1. Variable declaration and initialization
    int a = 100;
    double b = 3.14159265358979;
    auto str = "Hello C++";          // auto infers const char* (pointer)
    string stdStr = "Hello Modern";   // standard library string object

    cout << "===== 1. Variable Types and Size Analysis =====" << endl;

    // Output integer info
    cout << "Variable a [int]:" << endl;
    cout << "  - Value: " << a << endl;
    cout << "  - Type: " << typeid(a).name() << endl;
    cout << "  - Size: " << sizeof(a) << " bytes" << endl << endl;

    // Output auto-deduced string pointer info
    cout << "Variable str [auto -> const char*]:" << endl;
    cout << "  - Content: " << str << endl;
    cout << "  - Type: " << typeid(str).name() << " (P = Pointer, K = Konst, c = char)" << endl;
    cout << "  - Size: " << sizeof(str) << " bytes (pointer is always 8 bytes on 64-bit systems)" << endl << endl;

    // Output standard string object info
    cout << "Variable stdStr [std::string]:" << endl;
    cout << "  - Size: " << sizeof(stdStr) << " bytes (size of the object itself, not the string length)" << endl << endl;

    cout << "===== 2. Floating-Point Precision Control (setprecision) =====" << endl;

    // Default output (usually shows 6 significant digits)
    cout << "Default display of b: " << b << endl;

    // Use setprecision to control significant digits
    cout << "Significant digits (4): " << setprecision(4) << b << endl;

    // Combine with fixed to control decimal places (most common for currency or scientific calculations)
    cout << fixed << setprecision(2);
    cout << "Fixed decimal (2 places): " << b << endl;

    cout << fixed << setprecision(10);
    cout << "Fixed decimal (10 places): " << b << endl;

    // Use setw to create a simple table
    cout << "\n===== 3. Table Formatting Demo =====" << endl;
    cout << setfill('-'); // set fill character
    cout << setw(30) << "-" << endl;
    cout << setfill(' '); // reset fill to space
    cout << left << setw(15) << "Item Name" << right << setw(15) << "Value" << endl;
    cout << left << setw(15) << "int a"    << right << setw(15) << a << endl;
    cout << left << setw(15) << "double b" << right << setw(15) << fixed << setprecision(2) << b << endl;

    return 0;
}
#include <iostream>
#include <iomanip>  // this header must be included
#include <string>

using namespace std;

int main() {
    // Prepare test data
    string item1 = "Apple", item2 = "Banana", item3 = "Dragon Fruit (Sale)";
    double price1 = 50.0;
    double price2 = 12.3456;
    double price3 = 1234.5;

    cout << "========== Shopping Receipt Example ==========" << endl;

    // 1. Use setw() to set column width, left/right to set alignment
    // Note: setw only applies to the "next" output item
    cout << left << setw(20) << "Item Name"
        << right << setw(10) << "Unit Price" << endl;

    // 2. Use setfill() to change the fill character (default is space)
    cout << setfill('-') << setw(30) << "-" << endl;
    cout << setfill(' '); // remember to reset to space after use, otherwise everything after will be filled with dashes

    // 3. Use fixed with setprecision(n) to force n decimal places
    cout << fixed << setprecision(2);

    cout << left << setw(20) << item1 << right << setw(10) << price1 << endl;
    cout << left << setw(20) << item2 << right << setw(10) << price2 << endl;
    cout << left << setw(20) << item3 << right << setw(10) << price3 << endl;

    cout << setfill('=') << setw(30) << "=" << endl;
    cout << setfill(' ');

    // 4. Scientific notation output demo
    cout << "Total (scientific notation): " << scientific << 1296.8456 << endl;

    return 0;
}
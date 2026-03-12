#include <iostream>
#include <iomanip>  // required for setw, setfill, fixed, setprecision, scientific
#include <string>

using namespace std;

int main() {
    // Some sample data for a fake receipt
    string item1 = "Apple", item2 = "Banana", item3 = "Dragon Fruit (Sale)";
    double price1 = 50.0;
    double price2 = 12.3456;
    double price3 = 1234.5;

    cout << "========== Shopping Receipt ==========" << endl;

    // setw(n) reserves n characters of space for the next output
    // left/right decides which side to align the text to
    // Note: setw only affects the VERY NEXT thing you print, then it resets
    cout << left << setw(20) << "Item"
         << right << setw(10) << "Price" << endl;

    // setfill changes what character fills the empty space (default is a space)
    cout << setfill('-') << setw(30) << "-" << endl;
    cout << setfill(' '); // always reset this back to space or it'll keep filling with dashes

    // fixed + setprecision(2) means always show exactly 2 decimal places
    cout << fixed << setprecision(2);

    cout << left << setw(20) << item1 << right << setw(10) << price1 << endl;
    cout << left << setw(20) << item2 << right << setw(10) << price2 << endl;
    cout << left << setw(20) << item3 << right << setw(10) << price3 << endl;

    cout << setfill('=') << setw(30) << "=" << endl;
    cout << setfill(' ');

    // scientific notation - useful when numbers are very big or very small
    cout << "Total (scientific notation): " << scientific << 1296.8456 << endl;

    return 0;
}
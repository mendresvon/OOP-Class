#include <iostream>

using namespace std;
int main(){
    double n;
    cout << "Enter a floating point number: ";
    cin >> n;

    int integer_part = static_cast<int>(n);
    double decimal_part = n - integer_part;
    double sum = integer_part + decimal_part;

    cout << "Integer Part: " << integer_part << endl;
    cout << "Decimal Part: " << decimal_part << endl;
    cout << "Sum: " << sum << endl;

    return 0;
}
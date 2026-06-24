#include <iostream>

using namespace std;
int main(){
    float input;
    cout << "Enter a floating point number: ";
    cin >> input;

    int integer_part = static_cast<int>(input);
    float decimal_part = input - integer_part;
    float sum = integer_part + decimal_part;

    cout << "Integer Part: " << integer_part << endl;
    cout << "Decimal Part: " << decimal_part << endl;
    cout << "Sum: " << sum << endl;

    return 0;
}
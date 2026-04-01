// complex.cpp
// Complex number addition and subtraction using operator overloading
// No class: uses struct + non-member operator functions

#include <iostream>
using namespace std;

// --- data type ---
struct Complex {
    double real;
    double imag;
};

// --- operator overloading ---

// Addition: (a+bi) + (c+di) = (a+c) + (b+d)i
Complex operator+(const Complex &a, const Complex &b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

// Subtraction: (a+bi) - (c+di) = (a-c) + (b-d)i
Complex operator-(const Complex &a, const Complex &b) {
    Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

// Output stream: prints in "a + bi" or "a - bi" form
ostream &operator<<(ostream &os, const Complex &c) {
    os << c.real;
    if (c.imag >= 0)
        os << " + " << c.imag << "i";
    else
        os << " - " << -c.imag << "i";
    return os;
}

// --- main ---
int main() {
    Complex a = {3.0,  4.0};   // 3 + 4i
    Complex b = {1.0, -2.0};   // 1 - 2i

    cout << "a     = " << a << "\n";
    cout << "b     = " << b << "\n\n";
    cout << "a + b = " << (a + b) << "\n";
    cout << "a - b = " << (a - b) << "\n\n";

    cout << "Enter two complex numbers\n";
    cout << "  a (real imag): ";
    Complex x, y;
    cin >> x.real >> x.imag;
    cout << "  b (real imag): ";
    cin >> y.real >> y.imag;

    cout << "\na     = " << x << "\n";
    cout << "b     = " << y << "\n";
    cout << "a + b = " << (x + y) << "\n";
    cout << "a - b = " << (x - y) << "\n";

    return 0;
}

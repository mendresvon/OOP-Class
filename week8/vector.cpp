#include <iostream>
using namespace std;
 
class Vector {
public:
    double x, y;
    Vector(double x = 0, double y = 0) : x(x), y(y) {}
 
    Vector operator+(const Vector& rhs) const { return {x+rhs.x, y+rhs.y}; }
    Vector operator-(const Vector& rhs) const { return {x-rhs.x, y-rhs.y}; }
    Vector operator*(double s)          const { return {x*s, y*s}; }
    bool   operator==(const Vector& rhs)const { return x==rhs.x && y==rhs.y; }
    Vector& operator+=(const Vector& rhs) {
        x += rhs.x; y += rhs.y; return *this;
    }
    friend ostream& operator<<(ostream& os, const Vector& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;   // return os enables chaining: cout << a << b
    }
};
 
int main() {
    Vector a(1, 2), b(3, 4);
    cout << "a+b = " << a + b << endl;  // → (4, 6)
    cout << "a-b = " << a - b << endl;  // → (-2, -2)
    cout << "a*3 = " << a * 3 << endl;  // → (3, 6)
    cout << (a == b)  << endl;            // → 0 (false)
    a += b;
    cout << "a after +=: " << a << endl; // → (4, 6)
    return 0;
}

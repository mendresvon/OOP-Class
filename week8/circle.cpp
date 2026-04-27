#include <iostream>
#include <string>
using namespace std;

class Shape {
protected:
    string color;
public:
    Shape(string c) : color(c) {}
    void printColor() { cout << "Color: " << color << endl; }
};
 
class Circle : public Shape {
    double radius;
public:
    Circle(string c, double r) : Shape(c), radius(r) {}  // forward to base
    void printInfo() {
        printColor();
        cout << "Radius: " << radius << endl;
    }
};
 
int main() {
    Circle ci("Red", 5.0);
    ci.printInfo();
    return 0;
}

#include <iostream>
using namespace std;
 
// ── Abstract base ─────────────────────────────────────────────
class Shape {
public:
    virtual double area() const = 0;      // pure virtual
    virtual string name() const = 0;
    virtual void describe() const {
        cout << name() << " | area = " << area() << endl;
    }
    bool operator<(const Shape& rhs) const { return area() < rhs.area(); }
    bool operator==(const Shape& rhs) const { return area() == rhs.area(); }
    virtual ~Shape() {}
};
 
// ── Concrete classes ──────────────────────────────────────────
class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() const override { return M_PI * r * r; }
    string name() const override { return "Circle"; }
};
 
class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
    string name() const override { return "Rectangle"; }
};
 
int main() {
    Shape* shapes[] = {
        new Circle(3.0),       // area ≈ 28.27
        new Rectangle(4, 6),   // area = 24
    };
    for (auto s : shapes) s->describe();   // virtual dispatch
 
    if (*shapes[1] < *shapes[0])
        cout << shapes[1]->name() << " is smaller" << endl;
 
    for (auto s : shapes) delete s;
    return 0;
}

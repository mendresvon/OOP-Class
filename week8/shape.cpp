#include <iostream>
using namespace std;

class Shape { // abstract — cannot instantiate
public:
  virtual double area() = 0;      // pure virtual
  virtual void describe() const { // regular virtual — has a default body
    cout << "I am a shape" << endl;
  }
  virtual ~Shape() {}
};

class Rectangle : public Shape {
  double w, h;

public:
  Rectangle(double w, double h) : w(w), h(h) {}
  double area() override { return w * h; }
};

class Triangle : public Shape {
  double base, height;

public:
  Triangle(double b, double h) : base(b), height(h) {}
  double area() override { return 0.5 * base * height; }
};

int main() {
  Shape *shapes[] = {new Rectangle(4, 5), new Triangle(3, 6)};
  for (auto s : shapes) {
    s->describe();
    cout << "Area = " << s->area() << endl;
    delete s;
  }
  return 0;
}
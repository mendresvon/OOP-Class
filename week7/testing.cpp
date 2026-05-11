#include <iostream>
using namespace std;

class Car {
public:
  string brand;
  int year;

  void display() { cout << brand << " (" << year << ")" << endl; }
};

int main() {
  Car c; // instantiate an object
  c.brand = "Toyota";
  c.year = 2024;
  c.display(); // → Toyota (2024)
  return 0;
}

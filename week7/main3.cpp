#include <iostream>
using namespace std;

// Base class
class Drink {
protected:
  string name;
  double price;

public:
  Drink(string n, double p) : name(n), price(p) {}
  void display() const { cout << name << " — $" << price << endl; }
};

// Derived class — PearlMilkTea IS-A Drink
class PearlMilkTea : public Drink {
private:
  string pearlType;

public:
  PearlMilkTea(string n, double p, string pt) : Drink(n, p), pearlType(pt) {}

  void display() const {
    cout << name << " (" << pearlType << " pearls) — $" << price << endl;
  }
};

int main() {
  Drink water("Mineral Water", 1.5);
  PearlMilkTea bbt("Classic Milk Tea", 4.5, "tapioca");
  water.display(); // Mineral Water — $1.5
  bbt.display();   // Classic Milk Tea (tapioca pearls) — $4.5
  return 0;
}

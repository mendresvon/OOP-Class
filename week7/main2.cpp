#include <iostream>
using namespace std;

class Book {
private:
  string title;
  double price;

public:
  // Default constructor — no parameters
  Book() : title("Unknown"), price(0.0) {
    cout << "Default constructor called" << endl;
  }

  // Parameterized constructor
  Book(string t, double p) : title(t), price(p) {
    cout << "Parameterized constructor called" << endl;
  }

  void display() const { cout << title << " — $" << price << endl; }
};

int main() {
  Book b1;                      // default constructor
  Book b2("C++ Primer", 49.99); // parameterized constructor
  b1.display();                 // Unknown — $0
  b2.display();                 // C++ Primer — $49.99
  return 0;
}
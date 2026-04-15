#include <iostream>
using namespace std;

// Naming convention demo
const double MAX_PRICE = 9999.99; // SCREAMING_SNAKE_CASE (constant)

class ShoppingCart { // PascalCase (class)
private:
  int itemCount; // camelCase (member variable)
  double totalPrice;

public:
  ShoppingCart() : itemCount(0), totalPrice(0.0) {} // PascalCase (constructor)

  void addItem(double price) { // camelCase (member function)
    itemCount++;
    totalPrice += price;
  }

  void displaySummary() const { // camelCase
    cout << "Items: " << itemCount << "  Total: $" << totalPrice << endl;
  }
};

int main() {
  ShoppingCart cart;
  cart.addItem(29.99);
  cart.addItem(14.50);
  cart.displaySummary(); // Items: 2  Total: $44.49
  return 0;
}

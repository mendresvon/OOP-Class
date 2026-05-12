#include <iostream>
#include <stdexcept>
using namespace std;

double divide(double a, double b) {
  if (b == 0)
    throw invalid_argument("Division by zero");
  return a / b;
}

int main() {
  try {
    cout << divide(10, 2) << endl; // → 5
    cout << divide(5, 0) << endl;  // throws!
  } catch (const invalid_argument &e) {
    cerr << "Caught: " << e.what() << endl;
  } catch (...) {
    cerr << "Unknown exception" << endl;
  }
  return 0;
}


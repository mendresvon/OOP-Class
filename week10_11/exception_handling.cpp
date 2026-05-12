#include <iostream>
#include <stdexcept>
using namespace std;

double divide(double a, double b) {
  // can't divide by zero so we throw an error
  if (b == 0)
    throw invalid_argument("Division by zero");
  return a / b;
}

int main() {
  try {
    cout << divide(10, 2) << endl; // this one is fine
    cout << divide(5, 0) << endl;  // this one will blow up
  } catch (const invalid_argument &e) {
    // catching the specific error we threw
    cerr << "Caught: " << e.what() << endl;
  } catch (...) {
    // catching anything else just in case
    cerr << "Unknown exception" << endl;
  }
  return 0;
}

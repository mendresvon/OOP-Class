#include <iostream>
using namespace std;

class Counter {
  int val;

public:
  Counter(int v = 0) : val(v) {}

  Counter &operator++() { // prefix  ++x  — return *this
    ++val;
    return *this;
  }
  Counter operator++(int) { // postfix  x++ — dummy int, return old copy
    Counter old = *this;
    ++val;
    return old;
  }
  int get() const { return val; }
};

int main() {
  Counter c(5);
  cout << (++c).get() << endl; // → 6  (increments first)
  cout << (c++).get() << endl; // → 6  (returns old, then increments)
  cout << c.get() << endl;     // → 7
}

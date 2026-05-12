#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  // 1. Simple lambda assigned to auto variable
  auto square = [](int x) { return x * x; };
  cout << square(5) << endl; // → 25

  // 2. Capture by value
  int threshold = 10;
  auto isAbove = [threshold](int x) { return x > threshold; };
  cout << isAbove(15) << endl; // → 1 (true)

  // 3. With STL sort — sort descending
  vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
  sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
  for (int x : v)
    cout << x << ' ';
  cout << endl; // → 9 6 5 4 3 2 1 1

  // 4. Capture by reference — modify outer variable
  int sum = 0;
  for_each(v.begin(), v.end(), [&sum](int x) { sum += x; });
  cout << "Sum: " << sum << endl;

  return 0;
}

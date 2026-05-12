#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  
  auto square = [](int x) { return x * x; };
  cout << square(5) << endl; 

  
  int threshold = 10;
  auto isAbove = [threshold](int x) { return x > threshold; };
  cout << isAbove(15) << endl; 

  
  vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
  sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
  for (int x : v)
    cout << x << ' ';
  cout << endl; 

  
  int sum = 0;
  for_each(v.begin(), v.end(), [&sum](int x) { sum += x; });
  cout << "Sum: " << sum << endl;

  return 0;
}

#include <iostream>
using namespace std;

// recursive function to find factorial
int factorial(int n) {
  // base case: 0! and 1! are both 1
  if (n <= 1)
    return 1;                  
  // n! = n * (n-1)!
  return n * factorial(n - 1); 
}

int main() {
  // testing with 5 factorial
  cout << "5! = " << factorial(5) << endl; 
  return 0;
}

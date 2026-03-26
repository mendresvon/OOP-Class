// write a c++ program using functions to check if a number is prime

#include <iostream>
using namespace std;

// Forward declaration (prototype) — tells the compiler isPrime exists
// before main sees it. The actual definition comes after main.
bool isPrime(int n);

int main() {
    int number;

    cout << "請輸入一個整數: ";
    cin >> number;

    if (isPrime(number)) {
        cout << number << " 是質數 (is a prime number)." << endl;
    } else {
        cout << number << " 不是質數 (is not a prime number)." << endl;
    }

    return 0;
}

// Definition of isPrime
bool isPrime(int n) {
    if (n < 2) return false;       // 0 and 1 are not prime
    if (n == 2) return true;       // 2 is the only even prime
    if (n % 2 == 0) return false;  // eliminate all other even numbers

    // Only check odd divisors up to sqrt(n)
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}
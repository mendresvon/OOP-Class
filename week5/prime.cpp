// prime.cpp
// Simple prime checker
// Usage:
//  1) Run without args: program asks for an integer input
//  2) Or provide one argument: prime.exe 97

#include <iostream>
#include <cmath>
#include <limits>
#include <string>

using namespace std;

// Check whether n is prime (suitable for general 64-bit use)
bool isPrime(unsigned long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // Test factors of form 6k-1 and 6k+1
    unsigned long long r = static_cast<unsigned long long>(sqrt((long double)n));
    for (unsigned long long f = 5; f <= r; f += 6) {
        if (n % f == 0) return false;
        unsigned long long f2 = f + 2; // 6k+1
        if (f2 <= r && n % f2 == 0) return false;
    }
    return true;
}

// Parse string to long long; return false on error
bool parseInteger(const string &s, long long &out) {
    try {
        size_t idx = 0;
        long long val = stoll(s, &idx, 10);
        if (idx != s.size()) return false;
        out = val;
        return true;
    } catch (...) {
        return false;
    }
}

int main(int argc, char** argv) {
    long long n = 0;

    if (argc >= 2) {
        // use first argument
        string s = argv[1];
        if (!parseInteger(s, n)) {
            cerr << "Cannot parse input as integer: " << s << '\n';
            return 1;
        }
    } else {
        cout << "Enter an integer: ";
        if (!(cin >> n)) {
            cerr << "Failed to read input. Please enter a valid integer." << '\n';
            return 1;
        }
    }

    if (n < 0) {
        cout << n << " is negative; negatives are not considered prime." << '\n';
        return 0;
    }

    unsigned long long un = static_cast<unsigned long long>(n);
    bool prime = isPrime(un);

    if (prime) cout << n << " is prime." << '\n';
    else       cout << n << " is not prime." << '\n';

    return 0;
}

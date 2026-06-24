#include <iostream>
using namespace std;
bool is_prime(int n);

int main(){
    int n;
    cout << "Enter a number (n): ";
    cin >> n;
    cout << (is_prime(n) ? "Prime" : "Not Prime") << endl;
    return 0;
}

bool is_prime(int n){
    if (n <= 1) return false;
    for (int i=2; i*i <= n; i++){
        if (n % i == 0) return false;
    }
    return true;
}

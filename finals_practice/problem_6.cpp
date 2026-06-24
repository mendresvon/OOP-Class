#include <iostream>
using namespace std;

int main(){
    int n;
    cout << "Enter valid integer (-128 ~ 127): ";
    cin >> n;
    if (n < -128 || n > 127) {
        cout << "Not valid number.\n";
        return 0;
    }

    for (int i=7; i >= 0; i--) {
        cout << ((n >> i) & 1);
    }
    cout << endl;
    return 0;
}
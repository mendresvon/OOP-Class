#include <iostream>
#include <bitset>

using namespace std;
int main(){
    int n;
    cout << "Enter an integer (-128 ~ 127)";
    cin >> n;

    cout << bitset<8>(n) << endl;
    return 0;
}
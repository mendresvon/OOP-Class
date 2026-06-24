#include <iostream>

using namespace std;
int main(){
    int n1, n2;
    int count=0;

    cout << "Enter two numbers: ";
    cin >> n1 >> n2;

    if (n1 > n2){
        int temp = n1;
        n1 = n2;
        n2 = temp;
    }

    for (int i=1; i*i <= n2; i++){
        if (i*i >= n1 && i*i <= n2) count++;
    }

    cout << "Result: " << count << endl;
    return 0;
}
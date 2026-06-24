#include <iostream>

using namespace std;
int main(){
    int num1, num2;

    cout << "Enter 1st number: ";
    cin >> num1;
    cout << "Enter 2nd number: ";
    cin >> num2;

    if (num1 > num2){
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }

    int count = 0;
    for (int i=1; i*i <= num2; i++){
        if (i*i >= num1){
            count++;
        }
    }

    cout << count << endl;
    return 0;
}
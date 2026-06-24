#include <iostream>
using namespace std;

int main(){
    int n;
    int count_non_nega = 0, count_nega = 0;
    cout << "Enter a number: ";
    cin >> n;
    if (n == -9999){
        cout << "No valid number was entered.\n";
        return 0;
    }
    int max_val = n, min_val = n;
    if (n < 0) count_nega++;
    else count_non_nega++;

    while (true) {
        cout << "Enter a number: ";
        cin >> n;
        if (n == -9999) break;
        if (n > max_val) max_val = n;
        if (n < min_val) min_val = n;
        if (n < 0) count_nega++;
        else count_non_nega++;
    }

    cout << "Max: " << max_val << endl;
    cout << "Min: " << min_val << endl;
    cout << "Count (>= 0): " << count_non_nega << endl;
    cout << "Count (< 0): " << count_nega << endl;
    return 0;
}
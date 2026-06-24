#include <iostream>

using namespace std;

int main(){
    int pos_count = 0;
    int neg_count = 0;
    int max_val, min_val;
    int n;

    cout << "Enter a number: ";
    cin >> n;

    if (n == -9999) {
        cout << "No numbers were entered.\n";
        return 0;
    }

    min_val = n;
    max_val = n;
    if (n >= 0) pos_count++;
    else neg_count++;

    while (true){
        cout << "Enter a number: ";
        cin >> n;
        if (n == -9999) break;
        if (n >= 0) pos_count++;
        else neg_count++;
        if(n < min_val) min_val = n;
        if(n > max_val) max_val = n;
    }

    cout << "Count (>= 0): " << pos_count << endl;
    cout << "Count (< 0): " << neg_count << endl;
    cout << "Minimum Number: " << min_val << endl;
    cout << "Maximum Number: " << max_val << endl;
    
    return 0;
}
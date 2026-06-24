#include <iostream>
#include <string>
using namespace std;
int get_value(string card);

int main(){
    string card_1, card_2;
    cout << "Valid Cards: A 2 3 4 5 6 7 8 9 10 J Q K\n";
    cout << "Enter card 1 and card 2: ";
    cin >> card_1 >> card_2;

    int sum = get_value(card_1) + get_value(card_2);
    if (sum > 21) sum--;
    cout << "Sum: " << sum << endl;
    return 0;
}

int get_value(string card){
    if (card == "J" || card == "Q" || card == "K") return 10;
    else if (card == "A") return 11;
    else return stoi(card);
}
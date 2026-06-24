#include <iostream>
#include <string>

using namespace std;

int get_card_value(string card){
    if (card == "J" || card == "Q" || card == "K"){
        return 10;
    } else if (card == "A"){
        return 11;
    } else {
        return stoi(card);
    }
}

int main(){
    string card1, card2;
    cout << "Enter card 1 and card 2: ";
    cin >> card1 >> card2;

    int sum = get_card_value(card1) + get_card_value(card2);

    if (sum > 21) sum -= 1;

    cout << sum << endl;

    return 0;
}
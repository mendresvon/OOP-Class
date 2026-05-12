#include <iostream>
using namespace std;

void hanoi(int n, char from, char to, char via) {
    if (n == 0) return;
    hanoi(n - 1, from, via, to);
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    hanoi(n - 1, via, to, from);
}

int main() {
    hanoi(3, 'A', 'C', 'B');
    return 0;
}

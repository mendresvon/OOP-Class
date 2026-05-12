#include <iostream>
using namespace std;

// standard towers of hanoi puzzle using recursion
void hanoi(int n, char from, char to, char via) {
    // stop when there are no disks left
    if (n == 0) return;
    // move n-1 disks to the middle peg
    hanoi(n - 1, from, via, to);
    // move the biggest disk to the destination peg
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    // move those n-1 disks from the middle peg to the destination
    hanoi(n - 1, via, to, from);
}

int main() {
    // solving for 3 disks from A to C
    hanoi(3, 'A', 'C', 'B');
    return 0;
}

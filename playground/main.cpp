#include <iostream>
#include <ctime>

using namespace std;
int main() {
    srand(time(0));
    const int maxValue = 6;
    const int minValue = 1;
    int result = (rand() % (maxValue - minValue + 1)) + minValue;
    cout << "Result: " << result << endl;
}
#include <iostream>
#include <ctime>

using namespace std;
int main() {
    srand(time(0));
    const short maxValue = 6;
    const short minValue = 1;
    int result = (rand() % (maxValue - minValue) + 1) + minValue;
    cout << "Result: " << result << endl;
}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// a simple stack that can hold any type
template <typename T>
class Stack {
    vector<T> data;
public:
    void push(T val) { data.push_back(val); }
    void pop()       { data.pop_back(); }
    T top()    const { return data.back(); }
    bool empty() const { return data.empty(); }
};

int main() {
    // using it with integers
    Stack<int> si;
    si.push(1); si.push(2); si.push(3);
    cout << si.top() << endl;  

    // using the same class with strings
    Stack<string> ss;
    ss.push("hello"); ss.push("world");
    cout << ss.top() << endl;  

    return 0;
}

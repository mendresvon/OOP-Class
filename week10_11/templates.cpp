#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
    Stack<int> si;
    si.push(1); si.push(2); si.push(3);
    cout << si.top() << endl;  

    Stack<string> ss;
    ss.push("hello"); ss.push("world");
    cout << ss.top() << endl;  

    return 0;
}

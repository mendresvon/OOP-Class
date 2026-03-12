#include <iostream>
#include <string>

using namespace std;

// Week 2 - basics: reading user input and printing output
int main() {
    string name;
    int age;

    // Ask the user for some info
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your age: ";
    cin >> age;

    // Print it back
    cout << "Hello, " << name << "!" << endl;
    cout << "You are " << age << " years old." << endl;

    return 0;
}
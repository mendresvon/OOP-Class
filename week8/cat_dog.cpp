#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() {          // <<< virtual — runtime dispatch
        cout << "Animal sound" << endl;
    }
    virtual ~Animal() {}            // ALWAYS make destructor virtual in a base class
};
 
class Dog : public Animal {
public:
    void speak() override {         // override keyword (C++11) — strongly recommended
        cout << "Woof!" << endl;
    }
};
 
class Cat : public Animal {
public:
    void speak() override {
        cout << "Meow!" << endl;
    }
};
 
int main() {
    Animal* a1 = new Dog();
    Animal* a2 = new Cat();
    a1->speak();    // → Woof!  ✅ runtime dispatch
    a2->speak();    // → Meow!  ✅ runtime dispatch
    delete a1; delete a2;
}

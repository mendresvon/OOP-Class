#include <iostream>
#include <string>
using namespace std;

// ── Base class: Animal ──────────────────────────────────────────
class Animal {
protected:
  string name;
  int age;

public:
  // Parameterized constructor
  Animal(string n, int a) : name(n), age(a) {}

  void introduce() const { cout << "I am " << name << ", age " << age << endl; }
};

// ── Derived class: Dog (IS-A Animal) ─────────────────────────────
class Dog : public Animal {
private:
  string breed; // private data — only accessible via getter

public:
  Dog(string n, int a, string b) : Animal(n, a), breed(b) {}

  string getBreed() const { return breed; } // public getter

  void bark() const {
    cout << name << " says: Woof! (Breed: " << breed << ")" << endl;
  }
};

int main() {
  Animal generic("Generic Animal", 3);
  generic.introduce();

  Dog rex("Rex", 5, "Labrador");
  rex.introduce();                             // inherited from Animal
  rex.bark();                                  // Dog-specific behavior
  cout << "Breed: " << rex.getBreed() << endl; // via getter
  return 0;
}

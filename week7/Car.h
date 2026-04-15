// Car.h
#ifndef CAR_H // If CAR_H is not yet defined...
#define CAR_H // ...define it (marks this header as processed)

#include <string>
using namespace std;

class Car {
public:
  string brand;
  int year;
  Car(string b, int y);
  void display() const;
};

#endif // CAR_H  ← closes the #ifndef block

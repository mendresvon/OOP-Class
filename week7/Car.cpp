// Car.cpp
#include "Car.h"
#include <iostream>

Car::Car(string b, int y) : brand(b), year(y) {}

void Car::display() const { cout << brand << " (" << year << ")" << endl; }

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base class: Employee (using PascalCase for classes)
class Employee {
protected:
  string name;
  int id;
  double salary;

public:
  // Parameterized constructor using member initialization list
  Employee(string n, int i, double s) : name(n), id(i), salary(s) {}

  // Method to display basic info (using camelCase for methods)
  void displayInfo() const {
    cout << "ID: " << id << " | Name: " << name << " | Salary: $" << salary;
  }
};

// Derived class: Manager (IS-A Employee)
class Manager : public Employee {
private:
  int teamSize;

public:
  Manager(string n, int i, double s, int ts)
      : Employee(n, i, s), teamSize(ts) {}

  // Shadowing displayInfo to add Manager-specific details
  void displayInfo() const {
    Employee::displayInfo(); // Call base class method
    cout << " | Team Size: " << teamSize << " (Manager)" << endl;
  }
};

// Derived class: Developer (IS-A Employee)
class Developer : public Employee {
private:
  string programmingLanguage;

public:
  Developer(string n, int i, double s, string lang)
      : Employee(n, i, s), programmingLanguage(lang) {}

  // Shadowing displayInfo to add Developer-specific details
  void displayInfo() const {
    Employee::displayInfo(); // Call base class method
    cout << " | Language: " << programmingLanguage << " (Developer)" << endl;
  }
};

int main() {
  cout << "--- Employee Management System ---" << endl;

  // Create objects of derived classes
  Manager mgr("Alice Smith", 101, 85000.0, 5);
  Developer dev("Bob Johnson", 102, 75000.0, "C++");

  // Display information
  mgr.displayInfo();
  dev.displayInfo();

  return 0;
}

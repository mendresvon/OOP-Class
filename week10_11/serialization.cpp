#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Student {
  string name;
  int id;
  double gpa;

  void serialize(ofstream &out) const {
    out << name << '\n' << id << '\n' << gpa << '\n';
  }
  void deserialize(ifstream &in) {
    getline(in, name);
    in >> id >> gpa;
    in.ignore(); 
  }
};

int main() {
  Student s1 = {"Alice", 1001, 3.95};
  ofstream out("student.dat");
  s1.serialize(out);
  out.close();

  Student s2;
  ifstream in("student.dat");
  s2.deserialize(in);
  cout << s2.name << " | " << s2.id << " | " << s2.gpa << endl;
}

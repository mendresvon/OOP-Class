#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Student {
  string name;
  int id;
  double gpa;

  // saving student data to a file
  void serialize(ofstream &out) const {
    out << name << '\n' << id << '\n' << gpa << '\n';
  }
  // loading student data back from a file
  void deserialize(ifstream &in) {
    getline(in, name);
    in >> id >> gpa;
    in.ignore(); // skip the newline so it doesn't mess up the next read
  }
};

int main() {
  Student s1 = {"Alice", 1001, 3.95};
  // creating the data file
  ofstream out("student.dat");
  s1.serialize(out);
  out.close();

  Student s2;
  // reading it back to make sure it worked
  ifstream in("student.dat");
  s2.deserialize(in);
  cout << s2.name << " | " << s2.id << " | " << s2.gpa << endl;
}

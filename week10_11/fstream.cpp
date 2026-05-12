#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  // writing to a file
  ofstream ofs("output.txt");
  ofs << "Line 1" << endl;
  ofs << "Line 2" << endl;
  ofs.close();

  // reading from the same file
  ifstream ifs("output.txt");
  string line;
  while (getline(ifs, line)) {
    cout << line << endl;
  }
  ifs.close();
}

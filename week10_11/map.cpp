#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
  // making a score map
  map<string, int> scores;
  scores["Alice"] = 95;
  scores["Bob"] = 88;
  scores["Carol"] = 92;

  // printing everything in alphabetical order
  for (const auto &[name, score] : scores) {
    cout << name << ": " << score << endl;
  }

  // check if dave exists so we don't accidentally add him
  if (scores.count("Dave") == 0)
    cout << "Dave not found" << endl;

  // finding bob specifically
  auto it = scores.find("Bob");
  if (it != scores.end())
    cout << "Bob's score: " << it->second << endl;
}

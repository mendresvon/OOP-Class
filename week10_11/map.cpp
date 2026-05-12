#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
  map<string, int> scores;
  scores["Alice"] = 95;
  scores["Bob"] = 88;
  scores["Carol"] = 92;

  // Iteration (alphabetical order — maps are sorted by key)
  for (const auto &[name, score] : scores) {
    cout << name << ": " << score << endl;
  }

  // Check existence before access
  if (scores.count("Dave") == 0)
    cout << "Dave not found" << endl;

  // Find by key
  auto it = scores.find("Bob");
  if (it != scores.end())
    cout << "Bob's score: " << it->second << endl;
}

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// making our own error type for database stuff
class DatabaseError : public runtime_error {
  int errorCode;

public:
  DatabaseError(const string &msg, int code)
      : runtime_error(msg), errorCode(code) {}
  int code() const { return errorCode; }
};

int main() {
  try {
    // pretending something went wrong with the connection
    throw DatabaseError("Connection timeout", 503);
  } catch (const DatabaseError &e) {
    // catching our custom error and printing the code
    cerr << "DB Error [" << e.code() << "]: " << e.what() << endl;
  }
  return 0;
}

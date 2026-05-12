#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class DatabaseError : public runtime_error {
  int errorCode;

public:
  DatabaseError(const string &msg, int code)
      : runtime_error(msg), errorCode(code) {}
  int code() const { return errorCode; }
};

int main() {
  try {
    throw DatabaseError("Connection timeout", 503);
  } catch (const DatabaseError &e) {
    cerr << "DB Error [" << e.code() << "]: " << e.what() << endl;
  }
  return 0;
}

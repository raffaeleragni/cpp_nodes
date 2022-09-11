#include <iostream>
#include "lib.hpp"

using namespace std;

json ex1 = json::parse(R"(
{
  "test": true,
  "check": "done"
}
)");

int MyClass::main() {
  cout << "Output test." << endl << ex1 << endl;
  return 0;
}

#include <iostream>

struct C {
  C () { std::cout << "default ctor\n"; }
  C (int i) { std::cout << i << ": int ctor\n"; }
};

C c1();
C c2({});
C c3[1](1);
C c4[1]({});

class D {
  C c5();
  // C c6({});
} d;

int main () {
  C c7();
  C c8({});
}

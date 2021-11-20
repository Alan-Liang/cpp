#include <iostream>

class Foo {
 public:
  Foo () {}
  Foo (const Foo &other) {
    if (&other == this) std::cout << "!!!" << std::endl;
  }
};

int main () {
  Foo x = Foo(x);
  return 0;
}

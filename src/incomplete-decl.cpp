#include <iostream>

using std::cin, std::cout, std::endl;

class Foo {
  struct Bar1 { Foo baz; };

  template <typename T>
  struct Bar2 { T baz; };
  using Bar3 = Bar2<Foo>;
};

int main () {
  return 0;
}

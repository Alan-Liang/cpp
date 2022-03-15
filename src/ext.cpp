#include <iostream>

using std::cin, std::cout, std::endl;

struct A {
 public: int foo () { return 1; }
};
struct B:private A {
 public: int foo () { return 2; }
};
struct C:public B {
 private: int foo () { return 3; }
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout << B().foo() << endl;
  // cout << C().foo() << endl;
  return 0;
}

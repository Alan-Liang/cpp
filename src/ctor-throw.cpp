#include <iostream>

using std::cin, std::cout, std::endl;

#define p(x) cout << x << endl

class A {
 public:
  A () { p("ctor"); }
  A (int) { p("ctor throw"); throw 1; }
  ~A () { p("dtor"); }
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  delete new A;
  p("cp");
  try {
    delete new A(1);
  } catch (int i) {}
  p("end");
  delete new A(1);
  return 0;
}

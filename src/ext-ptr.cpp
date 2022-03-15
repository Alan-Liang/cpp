#include <iostream>

using std::cin, std::cout, std::endl;

class Base {
 public:
  virtual int get () { return 0; }
  virtual ~Base () {}
};

class Derived1 : public Base {
 public:
  int a;
  Derived1 (int a) : a(a) {}
  int get () { return 1; }
  int getA () { return a; }
};

class Derived2 : public Base {
 public:
  int get () { return 2; }
};

int main () {
  int i;
  cin >> i;
  Base *b;
  if (i == 1) b = new Derived1(19260817);
  else if (i == 2) b = new Derived2;
  else b = new Base;
  cout << b->get() << endl;
  if (i == 1) {
    cout << dynamic_cast<Derived1 *>(b)->getA() << endl;
  }
  delete b;
  return 0;
}

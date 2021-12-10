#include <iostream>

using std::cin, std::cout, std::endl;

class Base {
 protected:
  virtual void print () = 0;
 public:
  Base () { this->print(); }
};

class Derived : Base {
 protected:
  void print () {
    cout << "hello world" << endl;
  }
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  Derived d;
  return 0;
}

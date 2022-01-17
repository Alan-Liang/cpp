#include <iostream>

using std::cout;

class member {
 public:
  void operator<< (int) {
    cout << "m1\n";
  }
  void operator+= (int) {
    cout << "m2\n";
  }
};

class friend_ {
  friend void operator<< (const friend_ &, int) {
    cout << "f1\n";
  }
  friend void operator+= (const friend_ &, int) {
    cout << "f2\n";
  }
};

int main () {
  member m;
  friend_ f;
  m << 0;
  f << 0;
  m += 0;
  f += 0;
  return 0;
}

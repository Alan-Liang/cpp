#include <iostream>

using std::cin, std::cout, std::endl;

namespace sjtu {
class C {
 public:
  C &add (const C &b) {
    // C &sub (const C &a, const C &b);
    cout << "add" << endl;
    return sub(b);
  }
  C &sub (const C &b) {
    cout << "sub" << endl;
    return add(b);
  }
};
} // namespace sjtu

int main () {
  sjtu::C a, b;
  a.add(b);
  return 0;
}

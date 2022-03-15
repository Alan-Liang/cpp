#include <iostream>

using std::cin, std::cout, std::endl;

enum NatType { kNatZero, kNatS };
class Nat {
 public:
  NatType type;
  Nat *s = nullptr;
  constexpr bool operator== (const Nat &rhs) {
    return type == rhs.type && (*s == *rhs.s);
  }
};

template <typename A, A a, A b>
class Eq {
 private:
  Eq (int) {}
 public:
  static Eq<A, a, a> refl () {
    return Eq<A, a, a>(0);
  }
};

template <typename A, A a, A b>
Eq<A, b, a> x () {
  if constexpr (a == b) {
    return Eq<A, b, a>();
  }
}

int main () {
  return 0;
}

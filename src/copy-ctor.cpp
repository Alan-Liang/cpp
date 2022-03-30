#include <iostream>

using std::cout, std::endl;
#define print(x) cout << x << endl;

struct C {
  C () = default;
  C (const C &) {
    print("copy ctor");
  }
};

struct Foo {
  auto operator() (const C &) {
    print("foo");
  }
};
Foo foo;

struct T {
  C *c;
  T (int) : c(new C) {}
  auto g () const -> const C & { return *c; }
};

struct N {
  T t;
  N (int) : t(1) {}
};

auto main () -> int {
  const N *n = new N(1);
  foo(n->t.g());
  return 0;
}

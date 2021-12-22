#pragma once

struct D {
  D () = default;
  int f ();
};

// BAD
int D::f () {
  return 1;
}

template <int T>
struct C {
  C () = default;
  int f ();
};

template <int T>
int C<T>::f () {
  return T;
}

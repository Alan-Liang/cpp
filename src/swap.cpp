#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

// template <>
// auto std::swap<int *> (int *&a, int *&b) -> void {
//   std::cout << 1926 << endl;
// }

template <typename _Tp>
auto func (_Tp &&) -> void {}

auto func2 (int * const &) -> void {}

auto main () -> int {
  int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int b[11] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
  std::swap((int *&) a, (int *&) b);
  for (int i = 0; i < 10; ++i) std::cout << a[i] << ' ' << b[i] << std::endl;
  return 0;
}

#if false
auto main () -> int {
  int one = 1, two = 2;
  int a[one];
  int b[two];
  a[0] = 1;
  b[0] = 2;
  int c[10];
  func2(c);
  std::cout << &a[0] << ' ' << &b[0] << ' ' << a[0] << b[0] << std::endl;
  // std::swap((int *&) a, (int *&) b);
  // int *t = a;
  // (int *&) a = b;
  // (int *&) b = t;
  std::cout << (int *&)a << ' ' << (int *&) b << ' ' << a[0] << b[0] << std::endl;
  std::cout << std::is_move_constructible_v<int *> << std::is_move_assignable_v<int *> << std::endl; // 11
  int a[11] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int b[11] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
  std::swap(reinterpret_cast<int (&)[5]>(a), reinterpret_cast<int (&)[5]>(b));
  for (int i = 0; i < 10; ++i) std::cout << a[i] << ' ' << b[i] << std::endl;
}
#endif

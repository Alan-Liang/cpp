#include <iostream>

using std::cin, std::cout, std::endl;

auto fact (int n, int res = 1) -> int {
  if (n <= 1) return res;
  return fact(n - 1, res * n);
}

auto fib (int n = 1, int a = 1, int b = 1) -> int {
  if (n == 0) return a;
  if (n == 1) return b;
  return fib(n - 1, b, a + b);
}

auto main () -> int {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  return 0;
}

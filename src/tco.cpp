#include <iostream>

// factorial(x) = x!
// g++ -O2 optimizes both
// while g++ -O1 optimizes neither
int factorial (int n) {
  if (n == 1) return 1;
  return n * factorial(n - 1);
}

int factorialTail (int n, int current) {
  if (n == 1) return current;
  return factorialTail(n - 1, current * n);
}

int main () {
  std::cout << factorialTail(1000000, 1) << '\n';
  std::cout << factorial(1000000) << '\n';
}

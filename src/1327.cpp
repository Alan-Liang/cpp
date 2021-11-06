#include <iostream>

using std::cin, std::cout, std::endl;

template <typename T>
T pow (T base, int exponent, T modulo = 19260817) {
  base %= modulo;
  T power = 1;
  T exponentRemaining = exponent;
  T currentPosition = 0;
  T currentExp2 = base;
  while (exponentRemaining > 0) {
    T currentDigit = exponentRemaining % 2;
    exponentRemaining >>= 1;
    if (currentDigit == 1) power = (power * currentExp2) % modulo;
    currentExp2 = (currentExp2 * currentExp2) % modulo;
  }
  return power;
}

int main() {
    long long a = 10;
    unsigned int b = 10;
    short c = 10;
    long int d = 10;
    cout << pow(a, 2) << " " << pow(b, 2) << " " << pow(c, 2) << " " << pow(d, 2) << " " << endl;
    return 0;
}

#include <cmath>
#include <iostream>

using std::cin, std::cout, std::endl;

constexpr int modulo = 2019;

int main () {
  int base, exponent;
  cin >> base >> exponent;
  base %= modulo;
  int power = 1;
  int exponentRemaining = exponent;
  int currentPosition = 0;
  int currentExp2 = base;
  while (exponentRemaining > 0) {
    int currentDigit = exponentRemaining % 2;
    exponentRemaining >>= 1;
    if (currentDigit == 1) power = (power * currentExp2) % modulo;
    currentExp2 = (currentExp2 * currentExp2) % modulo;
  }
  cout << power << endl;

  return 0;
}

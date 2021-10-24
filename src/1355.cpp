#include "Function.hpp"

#include <iostream>

using std::cin, std::cout, std::endl;

void generate (int seed);
int getLen ();
/// [l, r] not [l, r)
int queryMin (int l, int r);
bool check (int index);

int main () {
  int seed, ans;
  cin >> seed;
  generate(seed);

  int length = getLen();
  int min = queryMin(0, length - 1);
  int interval = (length / 2) + (interval % 2);
  while (interval > 0) {
    int min1 = queryMin(ans, ans + interval - 1);
    if (min1 != min) ans += interval;
    if (interval == 1) break;
    interval = (interval / 2) + (interval % 2);
  }

  check(ans);
}

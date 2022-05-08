#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using std::cin, std::cout, std::endl;
constexpr int kMaxn = 4e5 + 10;
int array[kMaxn];

auto main () -> int {
  int length;
  scanf("%d", &length);
  for (int i = 1; i <= length; ++i) {
    scanf("%d", &array[i]);
    array[i] ^= array[i - 1];
  }
  int max = 0;
  for (int l1 = 1; l1 < length; ++l1) {
    for (int r1 = l1; r1 < length; ++r1) {
      for (int l2 = r1 + 1; l2 <= length; ++l2) {
        for (int r2 = l2; r2 <= length; ++r2) {
          int a = (array[r2] ^ array[l2 - 1]) + (array[r1] ^ array[l1 - 1]);
          max = std::max(a, max);
        }
      }
    }
  }
  printf("%d\n", max);
  return 0;
}

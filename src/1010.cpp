#include <iostream>

using std::cin, std::cout, std::endl;

#define MAXP 10000010

short ix[MAXP];

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  int current = 1;
  for (int i = 1; i <= n; ++i) {
    int count;
    cin >> count;
    if (count == 0) break;
    ix[current] = i;
    int count1 = count;
    while (--count) ix[current + count] = -count;
    current += count1;
  }
  for (int i = 0; i < m; ++i) {
    int query;
    cin >> query;
    int res = ix[query];
    if (res > 0) {
      cout << res << " 1\n";
    } else {
      cout << ix[query + res] << ' ' << 1 - res << '\n';
    }
  }
  return 0;
}

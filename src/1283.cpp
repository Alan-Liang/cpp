#include <algorithm>
#include <iostream>

using std::cin, std::cout, std::endl;

#define MAXN 1010
int dp[MAXN][MAXN];

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int size;
  cin >> size;
  for (int i = 1; i <= size; ++i) {
    for (int j = 1; j <= i; ++j) {
      int num;
      cin >> num;
      dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - 1]) + num;
    }
  }
  int max = 0;
  for (int i = 1; i <= size; ++i) {
    if (dp[size][i] > max) max = dp[size][i];
  }
  cout << max << endl;
  return 0;
}

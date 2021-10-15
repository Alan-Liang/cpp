#include<iostream>

#define MAXN 2001

int data[MAXN][MAXN];
int sum[MAXN][MAXN];
int m, n, k;

inline int presum (int i, int j) {
  return sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + data[i][j];
}

inline int calc (int x1, int y1, int x2, int y2) {
  return sum[x2 + 1][y2 + 1] - sum[x1][y2 + 1] - sum[x2 + 1][y1] + sum[x1][y1];
}

int main () {
  std::ios_base::sync_with_stdio(false);
  std::cin >> m >> n >> k;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> data[i][j];
      sum[i + 1][j + 1] = presum(i, j);
    }
  }
  for (int i = 0; i < k; i++) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << calc(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << '\n';
  }
  return 0;
}

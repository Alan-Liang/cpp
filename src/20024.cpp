#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

// #define int long long
const int kMaxn = 110;
const int kMaxm = 100010;
int price[kMaxn];
int data[kMaxn][kMaxm];
int base[kMaxm];
int n, m, k;
int q[kMaxn][kMaxm];
int left[kMaxn], right[kMaxn];

auto main () -> signed {
  scanf("%d%d%d", &n, &m, &k);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", price + i);
    sum += price[i];
  }
  sum *= k;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) scanf("%d", &data[i][j]);
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) base[i] += price[j] * data[j][i];
    if (i != 0) base[i] += base[i - 1];
  }
  int max = 0;
  for (int i = 0; i < m; ++i) {
    int extended = 0;
    int localmax = 0;
#define q q[j]
#define left left[j]
#define right right[j]
    for (int j = 0; j < n; ++j) {
      while (left <= right && data[j][q[right]] <= data[j][i]) --right;
      q[++right] = i;
      while (q[left] <= i - k) ++left;
      if (i >= k - 1) {
        localmax = std::max(localmax, data[j][q[left]]);
      }
    }
    extended = sum * localmax;
    if (i > k - 1) max = std::max(max, extended - (base[i] - base[i - k]));
    if (i == k - 1) max = std::max(max, extended - base[i]);
  }
  printf("%d\n", max);
  return 0;
}

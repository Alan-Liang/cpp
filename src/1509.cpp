#include <cstdio>
#include <cmath>
#include <iostream>

auto gcd (int a, int b) -> int {
  if (a < b) std::swap(a, b);
  if (b == 0) return a;
  return gcd(b, a % b);
}

constexpr int kMaxn = 5e5 + 10;
constexpr int kLogMaxn = std::log2(kMaxn) + 1;

int st[kLogMaxn][kMaxn];
int length, cntQueries;

auto read () -> void {
  scanf("%d%d", &length, &cntQueries);
  for (int i = 0; i < length; ++i) scanf("%d", &(st[0][i]));
}

auto makeSt () -> void {
  for (int i = 1; i < log2(length); ++i) {
    int span = 1 << i;
    for (int j = 0; j < length - span + 1; ++j) {
      st[i][j] = gcd(st[i - 1][j], st[i - 1][j + span / 2]);
    }
  }
}

auto queryOne (int l, int r) -> int {
  int span = r - l + 1;
  int level = log2(span);
  int dx = span - (1 << level);
  int resL = st[level][l];
  int resR = st[level][l + dx];
  return gcd(resL, resR);
}

auto queryFirst (int l, int r, int want) -> int {
  int initialL = l;
  int len = r - l;
  while (len > 0) {
    int half = len / 2;
    int mid = l + half;
    int res = queryOne(initialL, mid);
    if (res > want) {
      l = mid + 1;
      len -= half + 1;
    } else len = half;
  }
  return l;
}

auto queryLast (int l, int r, int want) -> int {
  int initialL = l;
  int len = r - l;
  while (len > 0) {
    int half = len / 2;
    int mid = l + half;
    int res = queryOne(initialL, mid);
    if (res < want) len = half;
    else {
      l = mid + 1;
      len -= half + 1;
    }
  }
  return l;
}

auto query () -> void {
  for (int i = 0; i < cntQueries; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    --l; --r;
    int gcd = queryOne(l, r);
    int first = queryFirst(l, r + 1, gcd);
    int last = queryLast(l, length, gcd);
    printf("%d %d\n", gcd, last - first - 1, last, first, r);
  }
}

auto main () -> int {
  read();
  makeSt();
  query();
  return 0;
}

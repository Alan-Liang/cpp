#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

#ifdef DEBUG
constexpr int kMaxn = 10;
#else
constexpr int kMaxn = 3000 + 10;
#endif
auto nextInt () -> int {
    char ch = getchar();
    if (ch == EOF) return -1;
    int x = 0, f = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
        if (ch == EOF) return -1;
    }
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int array[kMaxn][kMaxn];
int tree[kMaxn][4 * kMaxn];
int lazy[kMaxn][4 * kMaxn];
#define tree tree[__nt]
#define lazy lazy[__nt]
auto change (int __nt, int dx, int ix) {
  tree[ix] += dx;
  lazy[ix] += dx;
}
auto pushup (int __nt, int ix) -> void {
  tree[ix] = tree[ix * 2] + tree[ix * 2 + 1];
}
auto pushdown (int __nt, int ll, int rr, int ix) -> void {
  if (ll == rr) return;
  if (lazy[ix] == 0) return;
  change(__nt, lazy[ix], ix * 2);
  change(__nt, lazy[ix], ix * 2 + 1);
  lazy[ix] = 0;
}
auto build (int __nt, int ll, int rr, int ix) -> void {
  if (ll == rr) {
    tree[ix] = array[__nt][ll];
    return;
  }
  int mid = (ll + rr) / 2;
  build(__nt, ll, mid, ix * 2);
  build(__nt, mid + 1, rr, ix * 2 + 1);
  pushup(__nt, ix);
}
auto dec (int __nt, int dx, int left, int right, int ll, int rr, int ix) -> void {
  if (left <= ll && rr <= right) {
    change(__nt, dx, ix);
    return;
  }
  pushdown(__nt, ll, rr, ix);
  int mid = (ll + rr) / 2;
  if (left <= mid) dec(__nt, dx, left, right, ll, mid, ix * 2);
  if (right > mid) dec(__nt, dx, left, right, mid + 1, rr, ix * 2 + 1);
  pushup(__nt, ix);
}
auto query (int __nt, int left, int right, int ll, int rr, int ix) -> int {
  if (left <= ll && rr <= right) return tree[ix];
  pushdown(__nt, ll, rr, ix);
  int mid = (ll + rr) / 2;
  if (right <= mid) return query(__nt, left, right, ll, mid, ix * 2);
  if (left > mid) return query(__nt, left, right, mid + 1, rr, ix * 2 + 1);
  return query(__nt, left, right, ll, mid, ix * 2) + query(__nt, left, right, mid + 1, rr, ix * 2 + 1);
}
#undef tree
#undef lazy

auto main () -> int {
  int m = nextInt(), n = nextInt();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) array[i][j] = nextInt();
    build(i, 0, m - 1, 1);
  }
  while (true) {
    int op = nextInt(), y = nextInt() - 1, x = nextInt() - 1;
    if (op == -1) return 0;
    if (op == 1) {
      dec(x, nextInt(), y, y, 0, m - 1, 1);
    } else if (op == 2) {
      int a = nextInt();
      long long sum = 0;
      for (int i = 0; i < a; ++i) {
        sum += query(x - a + i, y - i, y + i, 0, m - 1, 1);
      }
      sum += query(x, y - a, y + a, 0, m - 1, 1);
      for (int i = 0; i < a; ++i) {
        sum += query(x + a - i, y - i, y + i, 0, m - 1, 1);
      }
      std::cout << sum << std::endl;
    }
  }
  return 0;
}

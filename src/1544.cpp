#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

#ifdef DEBUG
constexpr int kMaxn = 10;
#else
constexpr int kMaxn = 1e5 + 10;
#endif

struct Min {
  int num;
  int ix;
  auto operator+ (const Min &other) -> Min {
    if (num < 0) return other;
    if (other.num < 0) return *this;
    bool sel = true;
    if (other.num == num) sel = ix > other.ix;
    if (other.num < num) sel = false;
    return sel ? *this : other;
  }
};

int array[kMaxn];
Min tree[4 * kMaxn];
int lazy[4 * kMaxn];
auto change (int dx, int ix) {
  tree[ix].num -= dx;
  lazy[ix] += dx;
}
auto pushup (int ix) -> void {
  tree[ix] = tree[ix * 2] + tree[ix * 2 + 1];
}
auto pushdown (int ll, int rr, int ix) -> void {
  if (ll == rr) return;
  if (lazy[ix] == 0) return;
  change(lazy[ix], ix * 2);
  change(lazy[ix], ix * 2 + 1);
  lazy[ix] = 0;
}
auto build (int ll, int rr, int ix) -> void {
  if (ll == rr) {
    tree[ix] = { array[ll], ll };
    return;
  }
  int mid = (ll + rr) / 2;
  build(ll, mid, ix * 2);
  build(mid + 1, rr, ix * 2 + 1);
  pushup(ix);
}
auto dec (int dx, int left, int right, int ll, int rr, int ix) -> void {
  if (left <= ll && rr <= right) {
    change(dx, ix);
    return;
  }
  pushdown(ll, rr, ix);
  int mid = (ll + rr) / 2;
  if (left <= mid) dec(dx, left, right, ll, mid, ix * 2);
  if (right > mid) dec(dx, left, right, mid + 1, rr, ix * 2 + 1);
  pushup(ix);
}
auto query (int left, int right, int ll, int rr, int ix) -> Min {
  if (left <= ll && rr <= right) return tree[ix];
  pushdown(ll, rr, ix);
  int mid = (ll + rr) / 2;
  if (right <= mid) return query(left, right, ll, mid, ix * 2);
  if (left > mid) return query(left, right, mid + 1, rr, ix * 2 + 1);
  return query(left, right, ll, mid, ix * 2) + query(left, right, mid + 1, rr, ix * 2 + 1);
}
auto nextInt () -> int {
    char ch = getchar(); 
    int x = 0, f = 1;
    while(ch < '0' || ch > '9') 
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9') 
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    } 
    return x * f;
}

int res[kMaxn];
auto main () -> int {
#ifdef DEBUG
  freopen("1544.in", "r", stdin);
#endif
  int n = nextInt();
  for (int i = 0; i < n; ++i) {
    array[i] = i - nextInt();
  }
  build(0, n - 1, 1);
  for (int i = n; i >= 1; --i) {
    auto [ _, ix ] = query(0, n - 1, 0, n - 1, 1);
    res[ix] = i;
    if (ix + 1 != n) dec(1, ix + 1, n - 1, 0, n - 1, 1);
    dec(-n, ix, ix, 0, n - 1, 1);
#ifdef DEBUG
    if (ix == 0) {
      std::clog << "bp";
    }
    std::clog << ix << std::endl;
    for (int j = 0; j < n; ++j) std::clog << query(j, j, 0, n - 1, 1).num << ' ';
    std::clog << std::endl;
#endif
  }
  for (int i = 0; i < n; ++i) {
    printf("%d ", res[i]);
  }
  putchar('\n');
  return 0;
}

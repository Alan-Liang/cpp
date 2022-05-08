#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

auto nextInt () -> int;
auto readN (int *array, int n) -> void;
template <typename T>
auto print (const T &) -> void;
template <typename T>
auto println (const T &) -> void;
template <typename T>
auto printsp (const T &) -> void;
template <typename T>
struct Greater;
template <typename T>
struct Less;

#ifdef DEBUG
constexpr int kMaxn = 10;
#else
constexpr int kMaxn = 2e5 + 10;
#endif
double array[kMaxn];
double tree[4 * kMaxn];
double treesq[4 * kMaxn];
double lazy[4 * kMaxn];
auto sq (double x) -> double {
  return x * x;
}
auto pushup (int ix) -> void {
  tree[ix] = tree[ix * 2] + tree[ix * 2 + 1];
  treesq[ix] = treesq[ix * 2] + treesq[ix * 2 + 1];
}
auto build (int left, int right, int root) -> void {
  if (left == right) {
    tree[root] = array[left];
    treesq[root] = sq(array[left]);
    return;
  }
  int mid = (left + right) / 2;
  build(left, mid, root * 2);
  build(mid + 1, right, root * 2 + 1);
  pushup(root);
}
auto change (double dx, int ll, int rr, int ix) -> void {
  treesq[ix] += 2 * dx * tree[ix] + sq(dx) * (rr - ll + 1);
  tree[ix] += (rr - ll + 1) * dx;
  lazy[ix] += dx;
}
auto pushdown (int ll, int rr, int ix) -> void {
  if (lazy[ix] == 0.0) return;
  int mid = (ll + rr) / 2;
  change(lazy[ix], ll, mid, ix * 2);
  change(lazy[ix], mid + 1, rr, ix * 2 + 1);
  lazy[ix] = 0.0;
}
auto add (double dx, int left, int right, int ll, int rr, int ix) -> void {
  pushdown(ll, rr, ix);
  if (left <= ll && right >= rr) {
    change(dx, ll, rr, ix);
    return;
  }
  int mid = (ll + rr) / 2;
  if (left <= mid) add(dx, left, right, ll, mid, ix * 2);
  if (right > mid) add(dx, left, right, mid + 1, rr, ix * 2 + 1);
  pushup(ix);
}
struct Pair {
  double x, y;
  auto operator+ (const Pair &other) -> Pair {
    return { x + other.x, y + other.y };
  }
};
auto query (int left, int right, int ll, int rr, int ix) -> Pair {
  pushdown(ll, rr, ix);
  if (left <= ll && right >= rr) return { tree[ix], treesq[ix] };
  int mid = (ll + rr) / 2;
  if (right <= mid) return query(left, right, ll, mid, ix * 2);
  if (left > mid) return query(left, right, mid + 1, rr, ix * 2 + 1);
  return query(left, right, ll, mid, ix * 2) + query(left, right, mid + 1, rr, ix * 2 + 1);
}

auto main () -> int {
  int n = nextInt(), numOps = nextInt();
  for (int i = 0; i < n; ++i) {
    scanf("%lf", &array[i]);
  }
  build(0, n - 1, 1);
  for (int i = 0; i < numOps; ++i) {
    int op = nextInt(), left = nextInt() - 1, right = nextInt() - 1;
    if (op == 1) {
      double dx;
      scanf("%lf", &dx);
      add(dx, left, right, 0, n - 1, 1);
    } else if (op == 2) {
      double sum = query(left, right, 0, n - 1, 1).x / (right - left + 1);
      println((int) (sum * 100));
    } else if (op == 3) {
      auto [ s, ssq ] = query(left, right, 0, n - 1, 1);
      int length = right - left + 1;
      double res = ssq / length - sq(s / length);
      println((int) (res * 100));
    }
  }
  return 0;
}




auto nextInt () -> int {
  int i = 0, sign = 1;
  char c;
  while (!isdigit(c = getchar())) if (c == '-') sign = -1;
  do {
    i = i * 10 + c - '0';
  } while (isdigit(c = getchar()));
  return i * sign;
}

auto readN (int *array, int n) -> void {
  for (int i = 0; i < n; ++i) array[i] = nextInt();
}

template <>
auto print<int> (const int &val) -> void {
  printf("%d", val);
}
template <>
auto print<char> (const char &val) -> void {
  putchar(val);
}
template <>
auto print<char *> (char * const &val) -> void {
  printf("%s", val);
}
template <>
auto print<const char *> (const char * const &val) -> void {
  printf("%s", val);
}
template <>
auto print<long long> (const long long &val) -> void {
  printf("%lld", val);
}
template <>
auto print<unsigned long long> (const unsigned long long &val) -> void {
  printf("%llu", val);
}
template <typename T>
auto println (const T &val) -> void {
  print(val);
  putchar('\n');
}
template <typename T>
auto printsp (const T &val) -> void {
  print(val);
  putchar(' ');
}
template <typename T>
struct Greater {
  auto operator() (const T &lhs, const T &rhs) const -> bool {
    return lhs > rhs;
  }
};

template <typename T>
struct Less {
  auto operator() (const T &lhs, const T &rhs) const -> bool {
    return lhs < rhs;
  }
};

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

constexpr int kMaxn = 3e5 + 10;
constexpr int kModulo = 1926081733;
int mod[kMaxn] = { 1 };

struct Node {
  int normal, reversed, length;
  static auto h (int a, int b, int m) -> int {
    return ((long long) a * m + b) % kModulo;
  }
  auto operator+ (const Node &rhs) -> Node {
    return { h(normal, rhs.normal, mod[rhs.length]), h(rhs.reversed, reversed, mod[length]), length + rhs.length };
  }
};
Node tree[4 * kMaxn];
auto pushup (int ix) -> void {
  tree[ix] = tree[ix * 2] + tree[ix * 2 + 1];
}
auto init (int ll, int rr, int ix) -> void {
  if (ll == rr) {
    tree[ix].length = 1;
    return;
  }
  int mid = (ll + rr) / 2;
  init(ll, mid, ix * 2);
  init(mid + 1, rr, ix * 2 + 1);
  pushup(ix);
}
auto build (int target, int left, int right, int root) -> void {
  if (left == right) {
    tree[root] = { 1, 1, 1 };
    return;
  }
  int mid = (left + right) / 2;
  if (target <= mid) build(target, left, mid, root * 2);
  else build(target, mid + 1, right, root * 2 + 1);
  pushup(root);
}
auto query (int left, int right, int ll, int rr, int ix) -> Node {
  if (left <= ll && right >= rr) return tree[ix];
  int mid = (ll + rr) / 2;
  if (right <= mid) return query(left, right, ll, mid, ix * 2);
  if (left > mid) return query(left, right, mid + 1, rr, ix * 2 + 1);
  return query(left, right, ll, mid, ix * 2) + query(left, right, mid + 1, rr, ix * 2 + 1);
}

auto main () -> int {
  int length = nextInt();
  for (int i = 1; i <= length; ++i) {
    mod[i] = ((long long) mod[i - 1] * 2) % kModulo;
  }
  for (int i = 1; i <= length; ++i) {
    int pos = nextInt();
    build(pos, 1, length, 1);
    int l, r;
    if (pos * 2 <= length) {
      l = query(1, pos, 1, length, 1).reversed;
      r = query(pos, pos * 2 - 1, 1, length, 1).normal;
    } else {
      l = query(pos * 2 - length, pos, 1, length, 1).reversed;
      r = query(pos, length, 1, length, 1).normal;
    }
    // printf("%d %d\n", l, r);
    if (l == r) continue;
    printf("YES\n");
    return 0;
  }
  printf("NO\n");
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

#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

#ifdef DEBUG
#include <algorithm>
#endif

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

constexpr int kMaxn = 2e4 + 10;
constexpr int kMaxm = 1e5 + 10;
struct Node {
  union {
    struct {
      int a, b, c;
    };
    int v[3];
  };
  auto operator< (const Node &rhs) const -> bool {
    return c > rhs.c;
  }
};
Node nodes[kMaxm];
Node tmp[kMaxm];
int parent[kMaxn];
int enemy[kMaxn];

auto init (int n) -> void {
  for (int i = 1; i <= n; ++i) parent[i] = i;
}
auto get (int i) -> int {
  if (i == parent[i]) return i;
  return parent[i] = get(parent[i]);
}
auto join (int a, int b) -> void {
  if (enemy[a] == 0) enemy[a] = b;
  parent[get(b)] = get(enemy[a]);
}
auto sort (int left, int right) -> void {
  if (right - left <= 1) return;
  int mid = (left + right) / 2;
  sort(left, mid);
  sort(mid, right);
  int p = left;
  int q = mid;
  int s = left;
  while (s < right) {
    if (p >= mid || (q < right && nodes[q] < nodes[p])) tmp[s++] = nodes[q++];
    else tmp[s++] = nodes[p++];
  }
  for (int i = left; i < right; ++i) nodes[i] = tmp[i];
}


auto main () -> int {
  int n = nextInt(), m = nextInt();
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < 3; ++j) nodes[i].v[j] = nextInt();
  }
  sort(0, m);
  init(n);
  for (int i = 0; i < m; ++i) {
    auto &n = nodes[i];
    int s1 = get(n.a), s2 = get(n.b);
    if (s1 == s2) {
      println(n.c);
      return 0;
    }
    join(n.a, n.b);
    join(n.b, n.a);
  }
  println(0);
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

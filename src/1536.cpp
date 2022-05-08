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

using si = std::basic_string<int>;

constexpr int kMaxn = 2e5 + 10;

si edges[kMaxn];
int order[kMaxn];
int parent[kMaxn];
int sz[kMaxn];
bool ans[kMaxn];
bool open[kMaxn];

auto find (int x) -> int {
  if (parent[x] == x) return x;
  return parent[x] = find(parent[x]);
}

auto merge (int x, int y) -> void {
  int px = find(x), py = find(y);
  if (py == px) return;
  parent[py] = px;
  sz[px] += sz[py];
}

auto main () -> int {
  int n = nextInt(), m = nextInt();
  for (int i = 0; i < m; ++i) {
    int x = nextInt() - 1, y = nextInt() - 1;
    edges[x] += y;
    edges[y] += x;
  }
  for (int i = n - 1; i >= 0; --i) {
    order[i] = nextInt() - 1;
    parent[i] = i;
    sz[i] = 1;
  }
  for (int i = 0; i < n; ++i) {
    int x = order[i];
    open[x] = true;
    for (auto y : edges[x]) if (open[y]) merge(x, y);
    ans[i] = sz[find(x)] == i + 1;
  }
  for (int i = n - 1; i >= 0; --i) {
    puts(ans[i] ? "YES" : "NO");
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

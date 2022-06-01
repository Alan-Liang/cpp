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

constexpr int kMaxn = 1e5 + 10;
using si = std::basic_string<int>;

si edges[kMaxn];
int max[kMaxn];

auto dfs (int n) -> void {
  for (int to : edges[n]) {
    if (max[to] < max[n]) {
      max[to] = max[n];
      dfs(to);
    }
  }
}

auto main () -> int {
  int n = nextInt(), m = nextInt();
  for (int i = 0; i < m; ++i) {
    int from = nextInt() - 1, to = nextInt() - 1;
    edges[to] += from;
  }
  for (int i = 0; i < n; ++i) max[i] = i;
  for (int i = n - 1; i >= 0; --i) {
    if (max[i] == i) dfs(i);
  }
  for (int i = 0; i < n; ++i) {
    printsp(max[i] + 1);
  }
  putchar('\n');
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

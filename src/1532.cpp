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
constexpr int kMaxp = 2e5 + 10;
int a[kMaxn], b[kMaxn];

auto init (int *array, int n) -> void {
  for (int i = 1; i <= n; ++i) array[i] = i;
}
auto get (int *array, int i) -> int {
  if (array[i] == i) return i;
  return array[i] = get(array, array[i]);
}
auto join (int *array, int x, int y) -> void {
  int a = get(array, x), b = get(array, y);
  array[a] = b;
}
auto count (int *array, int n) -> int {
  int res = 0;
  int target = get(array, 1);
  for (int i = 1; i <= n; ++i) if (get(array, array[i]) == target) ++res;
  return res;
}

auto main () -> int {
  int n = nextInt(), m = nextInt(), p = nextInt(), q = nextInt();
  init(a, n);
  init(b, m);
  for (int i = 0; i < p; ++i) {
    int x = nextInt(), y = nextInt();
    if (x < 0 || y < 0) throw 1;
    join(a, x, y);
  }
  for (int i = 0; i < q; ++i) {
    int x = -nextInt();
    int y = -nextInt();
    if (x < 0 || y < 0) throw 1;
    join(b, x, y);
  }
  int x = count(a, n), y = count(b, m);
  println(std::min(x, y));
  return 0;
}




auto nextInt () -> int {
  int i;
  scanf("%d", &i);
  return i;
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

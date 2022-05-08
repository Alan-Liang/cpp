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

constexpr int kMaxn = 1e6 + 10;

int prev[kMaxn], next[kMaxn], str[kMaxn];
int hash[kMaxn];
int ans[kMaxn];
int powP[kMaxn];

constexpr int p = 19260817, mod = (1 << 30) - 1;

using ull = unsigned long long;
auto powInit () {
  powP[0] = 1;
  for (int i = 1; i < kMaxn; ++i) powP[i] = ((ull)powP[i - 1] * p) % mod;
}

auto main () -> int {
  powInit();
  int t = nextInt(), c = nextInt();
  for (int i = 0; i < t; ++i) {
    memset(prev, -1, sizeof(prev));
    int n = nextInt(), m = nextInt();
    for (int i = 0; i < n; ++i) {
      str[i] = nextInt();
      next[i] = -1;
    }
    int pattern = 0;
    for (int i = 0; i < m; ++i) {
      int x = nextInt();
      if (prev[x] != -1) pattern = ((ull)pattern * p + i - prev[x]) % mod;
      else pattern = ((ull)pattern * p) % mod;
      prev[x] = i;
    }
    memset(prev, -1, sizeof(prev));
    int h = 0;
    for (int i = 0; i < m; ++i) {
      if (prev[str[i]] != -1) {
        h = ((ull)h * p + i - prev[str[i]]) % mod;
        next[prev[str[i]]] = i;
      } else h = ((ull)h * p) % mod;
      prev[str[i]] = i;
    }
    int cnt = 0;
    for (int i = 0; i + m - 1 < n; ++i) {
      if (pattern == h) ans[cnt++] = i;
      if (prev[str[i + m]] > i) {
        h = ((ull)h * p + i + m - prev[str[i + m]]) % mod;
        next[prev[str[i + m]]] = i + m;
      } else h = ((ull)h * p) % mod;
      prev[str[i + m]] = i + m;
      if (next[i] != -1) {
        h = ((ull)h + mod - ((ull)(next[i] - i) * powP[i + m - next[i]]) % mod) % mod;
      }
    }
    println(cnt);
    for (int i = 0; i < cnt; ++i) printsp(ans[i] + 1);
    putchar('\n');
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

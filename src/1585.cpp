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
struct NotLess {
  auto operator() (const T &lhs, const T &rhs) const -> bool {
    return lhs >= rhs;
  }
};

template <typename T>
struct Less {
  auto operator() (const T &lhs, const T &rhs) const -> bool {
    return lhs < rhs;
  }
};

constexpr int kMaxn = 2e3 + 10;

int length;
int data[kMaxn];

template <typename Cmp>
struct C {
  Cmp lt;
  int dp[kMaxn];
  auto calc () -> int {
    dp[0] = 1;
    int max = 1;
    for (int i = 1; i < length; ++i) {
      dp[i] = 1;
      for (int j = 0; j < i; ++j) {
        if (!lt(data[j], data[i])) {
          max = std::max(max, dp[i] = std::max(dp[i], dp[j] + 1));
        }
      }
      // printsp(dp[i]);
    }
    return max;
  }
};
C<Less<int>> d;
C<NotLess<int>> a;

auto main () -> int {
  length = nextInt();
  readN(data, length);
  println(d.calc());
  println(a.calc());
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

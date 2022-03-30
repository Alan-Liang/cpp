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

#define int long long

#ifdef DEBUG
const int kMaxn = 10;
#else
const int kMaxn = 2e3 + 10;
#endif
int prefix[kMaxn][kMaxn];
int height, width;

// $\sum_{i=1}^{dw}\sum_{j=1}^{dh}\sum_{k=1}^{w-i+1}k(h-j+1)$
auto r1 (int x, int dx) -> int {
  return 3 * x * x - 3 * x * (dx - 2) + dx * dx - 3 * dx + 2;
}
auto r2 (int w, int h, int dw, int dh) {
  return dh * dw * (2 * h - dh + 1) * r1(w, dw) / 12;
}

auto main () -> signed {
  height = nextInt();
  width = nextInt();
  for (int i = 0; i < height; ++i) {
    int streak = 0;
    for (int j = 0; j < width; ++j) {
      char c = getchar();
      while (c != '.' && c != '#') c = getchar();
      if (c == '.') prefix[j][i + 1] = ++streak;
      else streak = 0;
    }
  }
  int sum = 0;
  for (int i = 0; i < width; ++i) {
    for (int j = 1; j < height + 2; ++j) {
      int top = j - 1;
      while (top > 0 && prefix[i][top] > prefix[i][j]) --top;
      while (top != j - 1) {
        ++top;
        int w = j - top;
        int h = prefix[i][top];
        int dh = h - prefix[i][j];
        sum += r2(w, h, 1, dh);
        prefix[i][top] = prefix[i][j];
      }
    }
  }
  println(sum);
  return 0;
}
#undef int




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

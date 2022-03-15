#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

// #define int long long

auto nextInt () -> int;
auto readN (int *array, int n) -> void;
template <typename T>
auto print (const T &) -> void;
template <typename T>
auto println (const T &) -> void;
template <typename T>
auto printsp (const T &) -> void;

const int kMaxn  = 2e5 + 10;
int length, numQueries;
int array[kMaxn];
const int logMaxn = std::log2(kMaxn) + 1;
int stMax[logMaxn][kMaxn];
int stMin[logMaxn][kMaxn];

auto makeSt () -> void {
  for (int i = 1; i <= log2(length); ++i) {
    int span = 1 << i;
    for (int j = 1; j <= length - span + 1; ++j) {
      stMax[i][j] = std::max(stMax[i - 1][j], stMax[i - 1][j + span / 2]);
      stMin[i][j] = std::min(stMin[i - 1][j], stMin[i - 1][j + span / 2]);
    }
  }
}

auto queryMax (int l, int r) -> int {
  int span = r - l + 1;
  int level = log2(span);
  int dx = span - (1 << level);
  int resL = stMax[level][l];
  int resR = stMax[level][l + dx];
  return std::max(resL, resR);
}

auto queryMin (int l, int r) -> int {
  int span = r - l + 1;
  int level = log2(span);
  int dx = span - (1 << level);
  int resL = stMin[level][l];
  int resR = stMin[level][l + dx];
  return std::min(resL, resR);
}

auto main () -> signed {
  length = nextInt(), numQueries = nextInt();
  readN(array + 1, length);
  for (int i = 1; i <= length; ++i) {
    array[i] -= nextInt();
    stMax[0][i] = stMin[0][i] = stMax[0][i - 1] + array[i];
  }
  makeSt();
  for (int i = 0; i < numQueries; ++i) {
    int l = nextInt();
    int r = nextInt();
    int startingPoint = stMax[0][l - 1];
    bool invalidSum = startingPoint != stMax[0][r];
    bool invalidTerminus = array[l] > 0 || array[r] < 0;
    bool invalidMax = queryMax(l, r) > startingPoint;
    if (invalidSum || invalidTerminus || invalidMax) println(-1);
    else println(startingPoint - queryMin(l, r));
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
auto print<signed> (const signed &val) -> void {
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

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

const int kMaxn = 1e6 + 10;
int length;
int state[kMaxn];
int zeroesBehind[kMaxn];
int onesAhead[kMaxn];
const int logMaxn = std::log2(kMaxn) + 1;
int sumSt[logMaxn][kMaxn];
int isRisingEdge[logMaxn][kMaxn];

auto makeSt (int (*st)[kMaxn]) -> void {
  for (int i = 1; i <= log2(length); ++i) {
    int span = 1 << i;
    for (int j = 0; j < length - span + 1; ++j) {
      st[i][j] = std::max(st[i - 1][j], st[i - 1][j + span / 2]);
    }
  }
}

auto query (int (*st)[kMaxn], int l, int r) -> int {
  int span = r - l + 1;
  int level = log2(span);
  int dx = span - (1 << level);
  int resL = st[level][l];
  int resR = st[level][l + dx];
  return std::max(resL, resR);
}

auto main () -> int {
  length = nextInt();
  int cntOps = nextInt();
  readN(state, length);
  zeroesBehind[0] = state[0] == 0 ? 1 : 0;
  for (int i = 1; i < length; ++i) {
    zeroesBehind[i] = zeroesBehind[i - 1] + (state[i] == 0 ? 1 : 0);
    isRisingEdge[0][i] = state[i - 1] == 0 && state[i] == 1;
  }
  for (int i = length - 1; i >= 0; --i) {
    onesAhead[i] = onesAhead[i + 1] + (state[i] == 1 ? 1 : 0);
    sumSt[0][i] = zeroesBehind[i] + onesAhead[i];
  }
  makeSt(sumSt);
  makeSt(isRisingEdge);
  for (int i = 0; i < cntOps; ++i) {
    int op = nextInt();
    int l = nextInt() - 1;
    int r = nextInt() - 1;
    if (op == 1) println(query(sumSt, l, r) - zeroesBehind[l - 1] - onesAhead[r + 1]);
    else println(l == r ? 1 : (query(isRisingEdge, l + 1, r) + 1));
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

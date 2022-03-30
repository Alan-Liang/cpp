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

const int kMaxn = 1e3 + 10;
struct Less {
  auto operator() (int a, int b) -> bool {
    return a < b;
  }
};
struct Greater {
  auto operator() (int a, int b) -> bool {
    return a > b;
  }
};
template <typename _Cmp>
struct Min {
  _Cmp cmp;
  int value[kMaxn] = {};
  Min (const int * const array, int length, int span) {
    int head = 0, tail = 0;
    int ixQueue[length] = {};
    for (int i = 0; i < length; ++i) {
      while (head < tail && !cmp(array[ixQueue[tail - 1]], array[i])) --tail;
      ixQueue[tail++] = i;
      if (ixQueue[head] <= i - span) ++head;
      if (i >= span - 1) {
        value[i - span + 1] = array[ixQueue[head]];
      }
    }
  }
};
int currentLine[kMaxn];
int min[kMaxn][kMaxn];
int max[kMaxn][kMaxn];

auto main () -> int {
  int height = nextInt(), width = nextInt(), span = nextInt();
  for (int i = 0; i < height; ++i) {
    readN(currentLine, width);
    Min<Less> lineMin(currentLine, width, span);
    Min<Greater> lineMax(currentLine, width, span);
    for (int j = 0; j < width - span + 1; ++j) {
      min[j][i] = lineMin.value[j];
      max[j][i] = lineMax.value[j];
    }
  }
  int dMin = 0x7f7f7f7f;
  for (int i = 0; i < width - span + 1; ++i) {
    Min<Less> colMin(min[i], height, span);
    Min<Greater> colMax(max[i], height, span);
    for (int j = 0; j < height - span + 1; ++j) {
      int d = colMax.value[j] - colMin.value[j];
      if (dMin > d) dMin = d;
    }
  }
  println(dMin);
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

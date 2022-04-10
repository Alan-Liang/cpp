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

#ifdef DEBUG
const int kMaxn = 4;
#else
const int kMaxn = 1e6 + 10;
#endif
// Array.from(Array(32).keys()).map(x => `1 << ${31 - x}`).join(', ')
const int pow2[] = { 1 << 31, 1 << 30, 1 << 29, 1 << 28, 1 << 27, 1 << 26, 1 << 25, 1 << 24, 1 << 23, 1 << 22, 1 << 21, 1 << 20, 1 << 19, 1 << 18, 1 << 17, 1 << 16, 1 << 15, 1 << 14, 1 << 13, 1 << 12, 1 << 11, 1 << 10, 1 << 9, 1 << 8, 1 << 7, 1 << 6, 1 << 5, 1 << 4, 1 << 3, 1 << 2, 1 << 1, 1 << 0 };
const int kBits = 32;

class Trie {
 public:
  int next[kMaxn * kBits][2] = {};
  int cnt = 0;

  auto insert (int num) -> void {
    int ixCurrent = 0;
    for (int i = 0; i < kBits; ++i) {
      int ch = (num & pow2[i]) == 0 ? 0 : 1;
      if (!next[ixCurrent][ch]) next[ixCurrent][ch] = ++cnt;
      ixCurrent = next[ixCurrent][ch];
    }
  }

  auto query (int num) -> int {
    int ixCurrent = 0;
    int result = 0;
    for (int i = 0; i < kBits; ++i) {
      int ch = (num & pow2[i]) == 0 ? 0 : 1;
      int want = ch == 0 ? 1 : 0;
      if (next[ixCurrent][want]) {
        result |= pow2[i];
        ixCurrent = next[ixCurrent][want];
      } else {
        ixCurrent = next[ixCurrent][ch];
      }
    }
    return result;
  }
};

Trie trie;

auto main () -> int {
  int length = nextInt(), numQueries = nextInt();
  for (int i = 0; i < length; ++i) trie.insert(nextInt());
  for (int i = 0; i < numQueries; ++i) println(trie.query(nextInt()));
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

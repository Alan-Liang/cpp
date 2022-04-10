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

const int kMaxn = 1e6 + 10;
int common[kMaxn];
std::string self, pattern;

auto nextCommon (int pos, char next) -> int {
  if (pos == 0) return 0;
  if (next == pattern[common[pos - 1]]) return common[pos - 1] + 1;
  return nextCommon(common[pos - 1], next);
}

auto prepare () -> void {
  for (int i = 0; i < pattern.length(); ++i) common[i] = nextCommon(i, pattern[i]);
}

auto query () -> void {
  int posStart = 0;
  for (int i = 0; i < self.length(); ++i) {
    if (self[i] == pattern[i - posStart]) {
      if (i - posStart == pattern.length() - 1) {
        std::cout << posStart + 1 << '\n';
        posStart = i - common[i - posStart] + 1;
      }
      continue;
    }
    if (i == posStart) {
      ++posStart;
      continue;
    }
    posStart = i - common[i - posStart - 1];
    --i;
  }
}

auto main () -> int {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  std::cin >> self >> pattern;
  prepare();
  query();
  for (int i = 0; i < pattern.length(); ++i) std::cout << common[i] << ' ';
  std::cout << std::endl;
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

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
const int kMaxn = 8;
#else
const int kMaxn = 1e6 + 10;
#endif
int left[kMaxn], right[kMaxn];
int queue[kMaxn];
int head, tail;
int length;


auto main () -> int {
  length = nextInt();
  int max = 0;
  int streakStartsAt = 0;
  for (int i = 0; i < length; ++i) left[i] = nextInt(), right[i] = nextInt();
  for (int i = 0; i < length; ++i) {
    while (head < tail && left[i] > left[queue[tail - 1]]) --tail;
    queue[tail++] = i;
    int currentUpperBound = right[i];
    while (head < tail - 1 && currentUpperBound < left[queue[head]]) {
      streakStartsAt = queue[head] + 1;
      ++head;
    }
    max = std::max(max, i - streakStartsAt + 1);
  }
  println(max);
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

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
const int kMaxn = 1e2 + 10;
#else
const int kMaxn = 1e6 + 10;
#endif

int array[kMaxn], stack[kMaxn];
int greaterLeft[kMaxn];

auto main () -> int {
  int length = nextInt();
  readN(array, length);
  int top = 0;
  stack[0] = -1;
  for (int i = 0; i < length; ++i) {
    while (top > 0 && array[stack[top]] < array[i]) --top;
    greaterLeft[i] = stack[top];
    stack[++top] = i;
  }
  top = 0;
  int max = 0;
  for (int i = 0; i < length; ++i) {
    while (top > 0 && array[stack[top]] >= array[i]) --top;
    int want = greaterLeft[i] + 1;
    int left = 1;
    int right = top;
    if (want == i || right == 0) goto next;
    while (left < right) {
      int mid = (left + right) / 2;
      if (stack[mid] >= want) right = mid;
      else left = mid + 1;
    }
    max = std::max(max, i - stack[left] + 1);
    // printsp(stack[left]);
    // println(i);
    next:
    stack[++top] = i;
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

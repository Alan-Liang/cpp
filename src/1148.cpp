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

using aull = std::basic_string<size_t>;
#ifdef DEBUG
constexpr int kMaxn = 8;
#else
constexpr int kMaxn = 5e4 + 10;
#endif
aull postfix[kMaxn];
int nextId = 1;

auto readstr () -> void {
  std::string str;
  char c;
  while (!isalpha(c = getchar())) continue;
  do str += c; while (isalpha(c = getchar()));
  std::hash<std::string_view> h;
  for (int i = str.length(); i >= 0; --i) postfix[nextId] += h(str.c_str() + i);
  nextId++;
}

auto main () -> int {
  int initialN = nextInt(), numQueries = nextInt();
  for (int i = 0; i < initialN; ++i) readstr();
  for (int i = 0; i < numQueries; ++i) {
    int op = nextInt();
    if (op == 1) readstr();
    else {
      int n = nextInt();
      int ref = nextInt();
      aull &pr = postfix[ref];
      int maxl = pr.length() - 1;
      for (int i = 1; i < n; ++i) {
        int self = nextInt();
        aull &ps = postfix[self];
        int l = 0, r = std::min(maxl, (int) ps.length() - 1);
        while (l < r) {
          int mid = (l + r) / 2 + ((l ^ r) & 1);
          if (pr[mid] == ps[mid]) l = mid;
          else r = mid - 1;
        }
        maxl = l;
      }
      println(maxl);
    }
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

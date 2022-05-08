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

constexpr int kMaxn = 2e5 + 10;
int buf[kMaxn];
int *array = buf + 1;
int tmp[kMaxn];

auto mergeSort (int left, int right) -> void {
  if (right - left <= 1) return;
  int mid = (left + right) / 2;
  mergeSort(left, mid);
  mergeSort(mid, right);
  int p = left;
  int q = mid;
  int s = left;
  while (s < right) {
    if (p >= mid || (q < right && array[p] > array[q])) tmp[s++] = array[q++];
    else tmp[s++] = array[p++];
  }
  for (int i = left; i < right; ++i) array[i] = tmp[i];
}

int tree[4 * kMaxn];
auto build (int left, int right, int root) -> void {
  if (left == right) {
    tree[root] = array[left];
    return;
  }
  int mid = (left + right) / 2;
  build(left, mid, root * 2);
  build(mid + 1, right, root * 2 + 1);
  tree[root] = std::max(tree[root * 2], tree[root * 2 + 1]);
}

auto lower (int left, int right, int target) -> int {
  while (left < right) {
    int mid = (left + right) / 2;
    if (array[mid] < target) left = mid + 1;
    else right = mid;
  }
  return left;
}
auto upper (int left, int right, int target) -> int {
  while (left < right) {
    int mid = (left + right) / 2;
    if (array[mid] <= target) left = mid + 1;
    else right = mid;
  }
  return left;
}

int f = 1;
auto main () -> int {
  int n = nextInt(), c = nextInt();
  if (c == 0) throw 1;
  if (c < 0) {
    c = -c;
    f = -1;
  }
  buf[0] = -0x7fffffff;
  array[n] = 0x7fffffff;
  readN(array, n);
  mergeSort(0, n);
  long long pairs = 0;
  for (int i = 0; i < n - 1;) {
    int num = array[i];
    int next = upper(i, n, num);
    int l = lower(next, n, num + c);
    int r = upper(l, n, num + c);
    pairs += (r - l) * (next - i);
    i = next;
  }
  println(pairs);
  return 0;
}




auto nextInt () -> int {
  int i = 0, sign = 1;
  char c;
  while (!isdigit(c = getchar())) if (c == '-') sign = -1;
  do {
    i = i * 10 + c - '0';
  } while (isdigit(c = getchar()));
  return i * sign * f;
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

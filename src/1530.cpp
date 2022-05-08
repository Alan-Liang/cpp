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

using H = unsigned;
constexpr int kMaxn = 1e3 + 10;
constexpr int kMaxm = 1e5 + 10;
int table[kMaxn];
H words[kMaxn];
int count[kMaxn];
int p[kMaxm];
H tmp[kMaxm];

constexpr H kM1 = (1U << 31) - 1;
constexpr int kM2 = 233;
auto hash (const char *str) -> H {
  int len = strlen(str);
  int val = len + 1;
  for (int i = 0; i < len; ++i) {
    val = ((unsigned long long) val * kM2 + str[i]) % kM1;
  }
  return val;
}

auto mergeSort (H *array, int left, int right) -> void {
  if (right - left <= 1) return;
  int mid = (left + right) / 2;
  mergeSort(array, left, mid);
  mergeSort(array, mid, right);
  int p = left;
  int q = mid;
  int s = left;
  while (s < right) {
    if (p >= mid || (q < right && array[p] > array[q])) tmp[s++] = array[q++];
    else tmp[s++] = array[p++];
  }
  for (int i = left; i < right; ++i) array[i] = tmp[i];
}

auto lower (H *first, H *last, H value) -> H * {
  int length = last - first;
  while (length != 0) {
    auto it = first;
    int mid = length / 2;
    it += mid;
    if (value > *it) {
      first = ++it;
      length -= mid + 1;
    } else {
      length = mid;
    }
  }
  return first;
}

auto main () -> int {
  int n = nextInt();
  for (int i = 0; i < n; ++i) {
    char buf[11];
    scanf("%s", buf);
    words[i] = hash(buf);
  }
  mergeSort(words, 0, n);
  int m = nextInt();
  int q = 0, l = 0;
  for (int i = 0; i < m; ++i) {
    char buf[11];
    scanf("%s", buf);
    unsigned h = hash(buf);
    int x = lower(words, words + n, h) - words;
    if (words[x] == h) {
      if (table[x] == 0) {
        table[x] = ++q;
        l = i;
      }
      p[i] = table[x];
    } else {
      p[i] = -1;
    }
  }
  println(q);
  int min = 0x7f7f7f7f;
  for (int i = 0; i <= l; ++i) {
    if (p[i] == -1) continue;
    ++count[p[i]];
  }
  int left = 0, right = l;
  while (right < m) {
    // for (int i = 0; i < 3; ++i) printsp(count[i + 1]); putchar('\n');
    for (; left < m; ++left) {
      if (p[left] == -1) continue;
      if (--count[p[left]] == 0) break;
    }
    if (left == m) break;
    // for (int i = 0; i < 3; ++i) printsp(count[i + 1]); putchar('\n');
    // printsp(left),printsp(right),println(min);
    min = std::min(min, right - left + 1);
    ++left;
    ++right;
    for (; right < m; ++right) {
      if (p[right] == -1) continue;
      if (count[p[right]]++ == 0) break;
    }
    // for (int i = 0; i < 3; ++i) printsp(count[i + 1]); putchar('\n');
  }
  println(min);
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

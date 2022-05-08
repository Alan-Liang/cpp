#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

#ifdef DEBUG
#include <algorithm>
#endif

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

constexpr int kMaxn = 110;
constexpr int kMaxm = 3e4 + 10;

using si = std::basic_string<int>;
using sv = std::string_view;

si edges[2 * kMaxn];
size_t hashes[kMaxm];
size_t tmp[kMaxm];
int numNodes, numGraphs;

auto sort (size_t *array, int left, int right) -> void {
  if (right - left <= 1) return;
  int mid = (left + right) / 2;
  sort(array, left, mid);
  sort(array, mid, right);
  int p = left;
  int q = mid;
  int s = left;
  while (s < right) {
    if (p >= mid || (q < right && array[p] > array[q])) tmp[s++] = array[q++];
    else tmp[s++] = array[p++];
  }
  for (int i = left; i < right; ++i) array[i] = tmp[i];
}

auto dfs (int curr, int parent) -> size_t {
  size_t hashes[edges[curr].size()];
  int i = 0;
  for (auto child : edges[curr]) {
    if (child == parent) continue;
    hashes[i] = dfs(child, curr);
    ++i;
  }
  sort(hashes, 0, i);
  return std::hash<sv>()(sv((char *) hashes, i * sizeof(hashes[0])));
}

auto readOne () -> size_t {
  int root = nextInt();
  for (int i = 0; i < numNodes; ++i) edges[i].clear();
  for (int i = 0; i < numNodes - 1; ++i) {
    int x = nextInt(), y = nextInt();
    edges[x] += y;
    edges[y] += x;
  }
  return dfs(root, root);
}

auto main () -> int {
  numNodes = nextInt();
  numGraphs = nextInt();
  for (int i = 0; i < numGraphs; ++i) hashes[i] = readOne();
  sort(hashes, 0, numGraphs);
  int max = 0;
  int streak = 1;
  for (int i = 1; i < numGraphs; ++i) {
    if (hashes[i - 1] == hashes[i]) ++streak;
    else streak = 1;
    max = std::max(max, streak);
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

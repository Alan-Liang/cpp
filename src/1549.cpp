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

constexpr int kMaxn = 1e3 + 10;
constexpr int kMaxm = 1e5 + 10;

int parent[kMaxn];

auto init (int n) -> void {
  for (int i = 0; i < n; ++i) parent[i] = i;
}
auto get (int x) -> int {
  if (parent[x] == x) return x;
  return parent[parent[x]] = get(parent[x]);
}
struct Edge {
  union {
    struct {
      int x, y, l;
    };
    int v[3];
  };
  auto operator< (const Edge &rhs) const -> bool {
    return l < rhs.l;
  }
};
Edge edges[kMaxm];

template <typename T>
auto sort (T *array, int l, int r) -> void {
  if (r - l <= 1) return;
  int mid = (l + r) / 2;
  sort(array, l, mid);
  sort(array, mid, r);
  T tmp[r - l + 1];
  int s = 0;
  int p = l;
  int q = mid;
  while (s < r - l) {
    if (p < mid && (q >= r || array[p] < array[q])) {
      tmp[s] = array[p];
      ++s; ++p;
    } else {
      tmp[s] = array[q];
      ++s; ++q;
    }
  }
  for (int i = 0; i < r - l; ++i) array[i + l] = tmp[i];
}

auto main () -> int {
  int n = nextInt(), m = nextInt(), k = nextInt();
  init(n);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < 3; ++j) {
      edges[i].v[j] = nextInt();
    }
  }
  sort(edges, 0, m);
  int c = n, ans = 0;
  for (int i = 0; i < m; ++i) {
    auto &edge = edges[i];
    int a = get(edge.x - 1), b = get(edge.y - 1);
    if (a == b) continue;
    parent[a] = b;
    ans += edge.l;
    --c;
    if (c == k) {
      println(ans);
      return 0;
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

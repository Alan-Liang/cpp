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

constexpr int kMaxn = 5e5 + 10;
struct Edge {
  union {
    struct {
      int from;
      int to;
      int cost, costb;
    };
    int v[4];
  };
  bool visited;
  auto operator< (const Edge &rhs) const -> bool {
    return cost < rhs.cost;
  }
};
Edge edges[kMaxn];
std::basic_string<int> eid[kMaxn];

int dfs[kMaxn], low[kMaxn];
int curr;
auto tarjan (int ix, int parent) -> void {
  low[ix] = dfs[ix] = ++curr;
  for (auto &id : eid[ix]) {
    auto &edge = edges[id];
    if (edge.visited) continue;
    edge.visited = true;
    auto to = edge.from == ix ? edge.to : edge.from;
    if (dfs[to] == 0) {
      tarjan(to, ix);
      if (low[to] > dfs[ix]) {
        edge.cost = edge.costb;
      }
      low[ix] = std::min(low[ix], low[to]);
    } else {
      low[ix] = std::min(low[ix], dfs[to]);
    }
  }
}

int parent[kMaxn];
auto init (int n) {
  if (n < 0) return;
  parent[n] = n;
  init(n - 1);
}
auto get (int n) {
  if (parent[n] == n) return n;
  return parent[n] = get(parent[n]);
}
auto join (int x, int y) {
  int a = get(x), b = get(y);
  if (a == b) return false;
  parent[a] = b;
  return true;
}

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
  int n = nextInt(), m = nextInt();
  for (int i = 0; i < m; ++i) {
    auto &e = edges[i];
    readN(e.v, 4);
    eid[e.from] += i;
    eid[e.to] += i;
  }
  tarjan(1, 1);
  sort(edges, 0, m);
  init(n);
  unsigned long long ans = 0;
  for (int i = 0; i < m; ++i) {
    auto &e = edges[i];
    if (join(e.from, e.to)) {
      ans += e.cost;
    }
  }
  println(ans);
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

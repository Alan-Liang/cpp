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

#define int long long

constexpr int kMaxn = 1e5 + 10;

struct Edge {
  union {
    struct {
      int from, to, weight;
    };
    int v[3];
  };
  auto operator< (const Edge &rhs) const -> bool {
    return weight < rhs.weight;
  }
};
Edge edges[kMaxn];

int nodes[kMaxn], parent[kMaxn];
int ans;
auto init (int n) {
  for (auto i = 0; i < n; ++i) {
    parent[i] = i;
    nodes[i] = 1;
  }
}
auto get (int n) {
  if (parent[n] == n) return n;
  return parent[parent[n]] = get(parent[n]);
}
auto join (const Edge &e) {
  int a = get(e.from - 1), b = get(e.to - 1);
  parent[a] = b;
  ans += e.weight;
  ans += (e.weight + 1) * (nodes[b] * nodes[a] - 1);
  // printsp(nodes[b]);
  // println(nodes[a]);
  nodes[b] += nodes[a];
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

auto main () -> signed {
  int nodes = nextInt();
  for (int i = 0; i < nodes - 1; ++i) {
    for (int j = 0; j < 3; ++j) edges[i].v[j] = nextInt();
  }
  sort(edges, 0, nodes - 1);
  init(nodes);
  for (int i = 0; i < nodes - 1; ++i) {
    // printsp(edges[i].from);
    // printsp(edges[i].to);
    // println(edges[i].weight);
    join(edges[i]);
  }
  println(ans);
  return 0;
}
#undef int




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

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

using ia = std::basic_string<int>;
#ifdef DEBUG
constexpr int kMaxn = 10;
#else
constexpr int kMaxn = 1e5 + 10;
#endif
constexpr int kBits = std::log2(kMaxn) + 1;
constexpr int kBitsInt = 32;

int parent[kMaxn][kBits + 1];
int iWeight[kMaxn][kBits + 1];
int depth[kMaxn];
ia children[kMaxn];
ia weight[kMaxn];

auto dfs (int current, int ixParent) -> void {
  parent[current][0] = ixParent;
  depth[current] = depth[ixParent] + 1;
  for (int i = 1; (1 << i) <= depth[current]; ++i) {
    parent[current][i] = parent[parent[current][i - 1]][i - 1];
    iWeight[current][i] = iWeight[parent[current][i - 1]][i - 1] + iWeight[current][i - 1];
  }
  for (int i = 0; i < children[current].size(); ++i) {
    int ixChild = children[current][i];
    if (ixChild == ixParent) continue;
    iWeight[ixChild][0] = weight[current][i];
    dfs(ixChild, current);
  }
}

struct Pair {
  int first;
  int second;
};

auto lca (int x, int y) -> Pair {
  if (x == y) return { x, 0 };
  auto result = 0;
  if (depth[x] < depth[y]) std::swap(x, y);
  for (int i = kBits; i >= 0; --i) {
    if (depth[parent[x][i]] >= depth[y]) {
      result += iWeight[x][i];
      x = parent[x][i];
    }
  }
  if (x == y) return { x, result };
  for (int i = kBits; i >= 0; --i) {
    if (parent[x][i] != parent[y][i]) {
      result += iWeight[x][i];
      result += iWeight[y][i];
      x = parent[x][i];
      y = parent[y][i];
    }
  }
  result += iWeight[x][0];
  result += iWeight[y][0];
  return { parent[x][0], result };
}

auto main () -> int {
  int numEdges = nextInt() - 1;
  for (int i = 0; i < numEdges; ++i) {
    int from = nextInt(), to = nextInt(), w = nextInt();
    children[from] += to;
    children[to] += from;
    weight[from] += w;
    weight[to] += w;
  }
  dfs(1, 0);
  int numQueries = nextInt();
  for (int i = 0; i < numQueries; ++i) {
    int a = nextInt(), b = nextInt(), c = nextInt();
    auto [ a1, d1 ] = lca(a, b);
    auto [ a2, d2 ] = lca(b, c);
    auto [ a3, d3 ] = lca(c, a);
    if (a1 == a2) println(d3 + lca(a3, b).second);
    else if (a2 == a3) println(d1 + lca(a1, c).second);
    else println(d2 + lca(a2, a).second);
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

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
constexpr int kMaxn = 1e5 + 10;
#else
constexpr int kMaxn = 1e5 + 10;
#endif
constexpr int kBits = std::log2(kMaxn) + 2;

int parent[kMaxn][kBits + 1];
int depth[kMaxn];
int weight[kMaxn];
ia children[kMaxn];

auto dfs (int current, int ixParent) -> void {
  parent[current][0] = ixParent;
  depth[current] = depth[ixParent] + 1;
  for (int i = 1; (1 << i) <= depth[current]; ++i) {
    parent[current][i] = parent[parent[current][i - 1]][i - 1];
  }
  for (int i = 0; i < children[current].size(); ++i) {
    int ixChild = children[current][i];
    if (ixChild == ixParent) continue;
    dfs(ixChild, current);
  }
}

auto lca (int x, int y) -> int {
  if (x == y) return x;
  if (depth[x] < depth[y]) std::swap(x, y);
  for (int i = kBits; i >= 0; --i) {
    if (depth[parent[x][i]] >= depth[y]) {
      x = parent[x][i];
    }
  }
  if (x == y) return x;
  for (int i = kBits; i >= 0; --i) {
    if (parent[x][i] != parent[y][i]) {
      x = parent[x][i];
      y = parent[y][i];
    }
  }
  return parent[x][0];
}

auto level (int x, int y) -> int {
  if (depth[x] < depth[y]) std::swap(x, y);
  for (int i = kBits; i >= 0; --i) {
    if (depth[parent[x][i]] >= depth[y] + 1) {
      x = parent[x][i];
    }
  }
  return x;
}

int max;

auto query (int curr, int ixParent) -> int {
  int sum = weight[curr];
  for (int c : children[curr]) {
    if (c == ixParent) continue;
    sum += query(c, curr);
  }
  max = std::max(max, sum);
  return sum;
}

auto main () -> int {
#ifdef DEBUG_VSCODE
  freopen("20044.in", "r", stdin);
#endif
  int numNodes = nextInt(), numAdd = nextInt();
  for (int i = 1; i < numNodes; ++i) {
    int x = nextInt(), y = nextInt();
    nextInt();
    children[x] += y;
    children[y] += x;
  }
  dfs(1, 0);
  for (int i = 0; i < numAdd; ++i) {
    int x = nextInt(), y = nextInt();
    int a = lca(x, y);
    ++weight[x];
    ++weight[y];
    --weight[a];
    --weight[parent[a][0]];
  }
  query(1, 0);
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

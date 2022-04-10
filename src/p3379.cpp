#include <iostream>
#include <cstdio>
#include <cmath>

using ia = std::basic_string<int>;
constexpr int kMaxn = 5e5 + 10;
constexpr int kBits = std::log2(kMaxn) + 1;

int parent[kMaxn][kBits + 1];
int depth[kMaxn];
ia edges[kMaxn];

auto dfs (int curr, int ixParent) -> void {
  parent[curr][0] = ixParent;
  depth[curr] = depth[ixParent] + 1;
  for (int i = 1; (1 << i) <= depth[curr]; ++i) {
    parent[curr][i] = parent[parent[curr][i - 1]][i - 1];
  }
  for (int i : edges[curr]) {
    if (i == ixParent) continue;
    dfs(i, curr);
  }
}

auto lca (int x, int y) -> int {
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

auto main () -> int {
  int n, m, s;
  scanf("%d%d%d", &n, &m, &s);
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    edges[x] += y;
    edges[y] += x;
  }
  dfs(s, 0);
  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", lca(a, b));
  }
  return 0;
}

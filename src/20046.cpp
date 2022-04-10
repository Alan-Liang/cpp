#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using std::cin, std::cout, std::endl;

#ifdef DEBUG
constexpr int kMaxn = 15;
#else
constexpr int kMaxn = 1e5 + 10;
#endif
constexpr int kBits = std::log2(kMaxn) + 1;
using ia = std::basic_string<int>;

int parent[kMaxn][kBits + 1];
int depth[kMaxn];
ia edges[kMaxn];

auto clear () -> void {
  memset(parent, 0, sizeof(parent));
  memset(depth, 0, sizeof(depth));
}

auto dfs (int curr, int ixParent) -> void {
  parent[curr][0] = ixParent;
  depth[curr] = depth[ixParent] + 1;
  for (int i = 1; (1 << i) <= depth[curr]; ++i) {
    parent[curr][i] = parent[parent[curr][i - 1]][i - 1];
  }
  for (auto i : edges[curr]) {
    if (i == ixParent) continue;
    dfs(i, curr);
  }
}

auto lca (int x, int y) -> int {
  if (x == y) return x;
  if (depth[x] < depth[y]) std::swap(x, y);
  for (int i = kBits; i >= 0; --i) {
    if (depth[parent[x][i]] >= depth[y]) x = parent[x][i];
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

auto isIn (int child, int parent) -> bool {
  if (depth[parent] > depth[child]) return false;
  return lca(parent, child) == parent;
}

auto main () -> int {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    clear();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n + 5; ++i) edges[i].clear();
    for (int i = 0; i < n - 1; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      edges[x] += y;
      edges[y] += x;
    }
    dfs(1, 0);
    for (int i = 0; i < m; ++i) {
      int x1, y1, x2, y2;
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      int a1 = lca(x1, y1);
      bool b1 = isIn(x2, a1);
      bool b2 = isIn(y2, a1);
      bool res;
      if (b1 != b2) {
        res = true;
      } else if (!b1 && !b2) {
        res = false;
      } else {
        int l1 = lca(x2, y2);
        res = isIn(x1, l1) || isIn(y1, l1);
      }
      printf(res ? "YES\n" : "NO\n");
    }
  }
  return 0;
}

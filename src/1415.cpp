#include <iostream>
#include <set>

using std::cin, std::cout, std::endl;

constexpr long long MAXN = 100010;

int dfsOrder[MAXN][2];

int dfs (const std::set<long long> &edges, int root) {
  const auto endIt = edges.upper_bound(root * MAXN + MAXN);
  int order = dfsOrder[root][0];
  for (auto it = edges.upper_bound(root * MAXN); it != endIt; ++it) {
    long long otherId = *it % MAXN;
    if (dfsOrder[otherId][0]) continue;
    dfsOrder[otherId][0] = ++order;
    order = dfsOrder[otherId][1] = dfs(edges, otherId);
  }
  return order;
}

int main () {
#ifdef DEBUG_VSCODE
  freopen("1415.in", "r", stdin);
#endif
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, q;
  cin >> n >> q;
  std::set<long long> edges;
  for (int i = 0; i < n - 1; ++i) {
    long long a, b;
    cin >> a >> b;
    edges.insert(a * MAXN + b);
    edges.insert(b * MAXN + a);
  }
  dfsOrder[1][0] = 1;
  dfsOrder[1][1] = dfs(edges, 1);
  for (int i = 0; i < q; ++i) {
    int x, y;
    cin >> x >> y;
    int ordX = dfsOrder[x][0];
    bool isAncestor = x != y && dfsOrder[y][0] <= ordX && ordX <= dfsOrder[y][1];
    cout << (isAncestor ? "Yes" : "No") << endl;
  }
  return 0;
}

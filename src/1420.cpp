#include <algorithm>
#include <iostream>

using std::cin, std::cout, std::endl;

constexpr int MAXN = 100010;
int num;
int w[MAXN];
using NodeId = int;
using EdgeId = int;
struct Edge {
  NodeId to;
  EdgeId prev;
};
Edge edges[2 * MAXN];
EdgeId last[MAXN];

EdgeId lastEdgeId = 0;
void addEdge (NodeId from, NodeId to) {
  edges[++lastEdgeId].to = to;
  edges[lastEdgeId].prev = last[from];
  last[from] = lastEdgeId;
}

int size[MAXN];

void dfs (NodeId root, NodeId father) {
  size[root] = w[root];
  for (EdgeId curr = last[root]; curr; curr = edges[curr].prev) {
    if (edges[curr].to == father) continue;
    dfs(edges[curr].to, root);
    size[root] += size[edges[curr].to];
  }
}

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> num;
  for (NodeId i = 0; i < num; ++i) cin >> w[i];
  for (EdgeId i = 0; i < num - 1; ++i) {
    int from, to;
    cin >> from >> to;
    addEdge(from, to);
    addEdge(to, from);
  }
  dfs(0, 0);
  for (NodeId i = 0; i < num; ++i) {
    cout << size[i] << endl;
  }
  return 0;
}

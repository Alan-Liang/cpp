#include <algorithm>
#include <iostream>

using std::cin, std::cout, std::endl;

int height, width, rooti, rootj;
constexpr int MAXN = 55;
bool map[MAXN][MAXN];
using NodeId = int;
using EdgeId = int;
struct Edge {
  NodeId to;
  EdgeId prev;
};
Edge edges[90000];
EdgeId last[MAXN * MAXN];

EdgeId lastEdgeId = 0;
void addEdge (NodeId from, NodeId to) {
  edges[++lastEdgeId].to = to;
  edges[lastEdgeId].prev = last[from];
  last[from] = lastEdgeId;
}

int _nid (int i, int j) { return i * MAXN + j; }

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> height >> width;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      while (cin.peek() == ' ' || cin.peek() == '\r' || cin.peek() == '\n') cin.get();
      char x = cin.get();
      map[i][j] = x == 'X';
      if (x == '*') {
        rooti = i;
        rootj = j;
      }
    }
  }
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (map[i][j]) continue;
      for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
          if (!di && !dj) continue;
          if (i + di < 0 || i + di >= height) continue;
          if (j + dj < 0 || j + dj >= width) continue;
          if (map[i + di][j + dj]) continue;
          add(_nid(i, j), _nid(i + di, j + dj));
          add(_nid(i + di, j + dj), _nid(i, j));
        }
      }
    }
  }
  std::cout << bfs() << std::endl;
  return 0;
}

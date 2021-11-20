#include <cassert>
#include <climits>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using std::cin, std::cout, std::endl;

constexpr int kMaxWidth = 39;
constexpr int kMaxHeight = 101;

char map[2 * kMaxHeight + 1][2 * kMaxWidth + 1];
int width, height;

enum Direction { UP, DOWN, LEFT, RIGHT };
constexpr int deltas[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

bool hasRoute (int i, int j, Direction dir) {
  switch (dir) {
    case UP: return map[2 * i][2 * j + 1] == ' ';
    case DOWN: return map[2 * i + 2][2 * j + 1] == ' ';
    case LEFT: return map[2 * i + 1][2 * j] == ' ';
    case RIGHT: return map[2 * i + 1][2 * j + 2] == ' ';
    default: assert(false);
  }
}

bool isExit (int i, int j) {
  if (i == 0 && hasRoute(i, j, UP)) return true;
  if (j == 0 && hasRoute(i, j, LEFT)) return true;
  if (i == height - 1 && hasRoute(i, j, DOWN)) return true;
  if (j == width - 1 && hasRoute(i, j, RIGHT)) return true;
  return false;
}

int bfs (int i, int j) {
  bool visited[height][width];
  memset(visited, 0, sizeof(visited));
  std::queue<std::tuple<int, int, int>> queue;
  if (isExit(i, j)) return 1;
  queue.emplace(std::tuple<int, int, int>(i, j, 1));
  while (queue.size() > 0) {
    const auto &[ i, j, depth ] = queue.front();
    queue.pop();
    if (isExit(i, j)) return depth;
    if (visited[i][j]) continue;
    visited[i][j] = true;
    for (Direction dir : { UP, DOWN, LEFT, RIGHT }) {
      if (hasRoute(i, j, dir)) {
        queue.emplace(std::tuple<int, int, int>(i + deltas[dir][0], j + deltas[dir][1], depth + 1));
      }
    }
  }
  assert(false);
}

int main () {
#ifdef DEBUG_VSCODE
  freopen("1416.in", "r", stdin);
#endif
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> width >> height;
  while (cin.peek() == '\r' || cin.peek() == '\n' || cin.peek() == ' ') cin.get();
  for (int i = 0; i < 2 * height + 1; ++i) {
    for (int j = 0; j < 2 * width + 1; ++j) map[i][j] = cin.get();
    cin.get();
  }
  int max = -1;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) max = std::max(max, bfs(i, j));
  }
  cout << max << endl;
  return 0;
}

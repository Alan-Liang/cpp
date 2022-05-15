#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

constexpr int kMaxn = 1e4 + 10;
constexpr int kMaxm = 3e4 + 10;

enum Type { kF = 0, kE = 1 };
struct Node {
  int parent;
  Type t;
  bool jammed;
};
Node nodes[kMaxn];
bool counted[kMaxn][3];

auto init (int n) -> void {
  for (int i = 1; i <= n; ++i) {
    nodes[i].parent = i;
    nodes[i].t = kF;
  }
}
auto query (int i) -> Node {
  auto &n = nodes[i];
  if (n.parent == i) return n;
  auto res = query(n.parent);
  n.t = res.t = Type(n.t ^ res.t);
  n.parent = res.parent;
  return n;
}
auto join (int a, int b, Type type) -> void {
  auto res = query(b);
  auto x = query(a);
  if (res.parent == x.parent) {
    if (res.t ^ x.t ^ type != 0) {
      nodes[res.parent].jammed = true;
    }
    return;
  }
  auto &n = nodes[res.parent];
  n.parent = x.parent;
  n.t = Type(x.t ^ res.t ^ type);
}
auto count (int n) -> int {
  int res = 0;
  for (int i = 1; i <= n; ++i) {
    auto r = query(i);
    if (!counted[r.parent][r.t]) {
      counted[r.parent][r.t] = true;
      ++res;
    }
    if (nodes[i].jammed) {
      if (!counted[r.parent][2]) {
        counted[r.parent][2] = true;
        --res;
      }
    }
  }
  return res;
}

auto main () -> int {
  int n, m;
  scanf("%d%d", &n, &m);
  init(n);
  for (int i = 0; i < m; ++i) {
    char op;
    int x, y;
    scanf(" %c%d%d", &op, &x, &y);
    join(x, y, op == 'E' ? kE : kF);
    if (op != 'E' && op != 'F') throw 1;
  }
  printf("%d\n", count(n));
  return 0;
}

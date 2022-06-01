#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

constexpr int kMaxn = 5e2 + 10;

auto nextInt() -> int {
  int n;
  scanf("%d", &n);
  return n;
}

struct {
  int x, y;
} pos[kMaxn];

auto pow2 (int a) -> int { return a * a; }
template <typename T>
auto d2 (T a, T b) -> double {
  return sqrt(pow2(a.x - b.x) + pow2(a.y - b.y));
}
struct Edge {
  int a, b;
  double dist;
  auto operator< (const Edge &rhs) const -> bool {
    return dist < rhs.dist;
  }
};
Edge edges[kMaxn * kMaxn];
int edgeCount = 0;

int parent[kMaxn];
auto init (int n) -> void {
  for (int i = 0; i < n; ++i) parent[i] = i;
}
auto get (int n) -> int {
  if (parent[n] == n) return n;
  return parent[parent[n]] = get(parent[n]);
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

auto main () -> int {
  int s = nextInt(), p = nextInt();
  if (s == 0) s = 1;
  for (int i = 0; i < p; ++i) {
    pos[i].x = nextInt();
    pos[i].y = nextInt();
    for (int j = 0; j < i; ++j) {
      double dist = d2(pos[i], pos[j]);
      edges[edgeCount++] = { i, j, dist };
    }
  }
  sort(edges, 0, edgeCount);
  init(p);
  int groups = p;
  for (int i = 0; i < edgeCount; ++i) {
    int a = get(edges[i].a), b = get(edges[i].b);
    if (a == b) continue;
    --groups;
    parent[a] = b;
    if (groups <= s) {
      printf("%.2lf\n", edges[i].dist);
      return 0;
    }
  }
  return 0;
}

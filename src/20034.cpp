#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

auto nextInt() -> int {
  int n;
  scanf("%d", &n);
  return n;
}

#define printfx(...) // printf(__VA_ARGS__)

// constexpr int kMaxn = 0 + 10;
constexpr int kMaxn = 5e4 + 10;
using si = std::basic_string<int>;

bool visited[kMaxn];
struct Edge {
  int to;
  bool visited;
};
std::basic_string<Edge> edges[kMaxn];

int dfn[kMaxn], low[kMaxn];
int curr;
bool cut[kMaxn];
auto tarjan (int ix, int pa) -> void {
  dfn[ix] = low[ix] = ++curr;
  int child = 0;
  bool root = ix == pa;
  for (auto &edge : edges[ix]) {
    if (edge.visited) continue;
    edge.visited = true;
    int ed = edge.to;
    if (dfn[ed] == 0) {
      ++child;
      tarjan(ed, ix);
      if (!root && low[ed] >= dfn[ix]) cut[ix] = true;
      low[ix] = std::min(low[ix], low[ed]);
    } else {
      low[ix] = std::min(low[ix], dfn[ed]);
    }
  }
  if (root && child >= 2) cut[ix] = true;
}

auto dfs (int n, int &cnt, int &cutid) -> void {
  ++cnt;
  printfx("dfs %d\n", n);
  visited[n] = true;
  for (auto &edge : edges[n]) {
    int i = edge.to;
    printfx("dfs edge %d - %d stat %d %d\n", n, i, visited[i], cut[i]);
    if (cut[i]) {
      if (cutid == -1) cutid = i;
      if (cutid != i) cutid = -2;
    }
    if (!visited[i] && !cut[i]) dfs(i, cnt, cutid);
  }
}

auto main () -> int {
  int _case = 1;
  while (true) {
    int n = nextInt();
    if (n == 0) return 0;

    #define clear(x) memset(x, 0, sizeof(x));
    clear(visited)
    clear(dfn)
    clear(low)
    clear(cut)
    #undef clear
    curr = 0;
    for (int i = 0; i < kMaxn; ++i) edges[i].clear();

    int m = 0;
    for (int i = 0; i < n; ++i) {
      int a = nextInt() - 1, b = nextInt() - 1;
      m = std::max(m, a);
      m = std::max(m, b);
      edges[a] += { b, 0 };
      edges[b] += { a, 0 };
    }
    ++m;
    tarjan(0, 0);

    unsigned long long ans = 1ull;
    int cuts = 0;
    for (int i = 0; i < m; ++i) {
      if (cut[i]) {
        printfx("Cut %d\n", i);
        continue;
      }
      if (visited[i]) continue;
      int t = 0, cutid = -1;
      dfs(i, t, cutid);
      if (cutid == -2) continue;
      ++cuts;
      if (cutid == -1 && t > 1) {
        ans *= t * (t - 1) / 2;
        ++cuts;
        continue;
      }
      printfx("dfs from %d sz %d\n", i, t);
      ans *= t;
    }
    printf("Case %d: %d %llu\n", _case, cuts, ans);
    ++_case;
  }
  return 0;
}

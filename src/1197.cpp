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

#ifdef DEBUG
constexpr int kMaxn = 10;
#else
constexpr int kMaxn = 5e5 + 10;
#endif
using si = std::basic_string<int>;

int money[kMaxn];
si edges[kMaxn];
bool terminator[kMaxn];
struct {
  int money;
  // si nodes;
  bool terminator;
  int max;
} groups[kMaxn];

int dfs[kMaxn], low[kMaxn], stack[kMaxn], groupix[kMaxn];
int curr, top, currentGroup;
bool visited[kMaxn], instack[kMaxn];
auto tarjan (int ix) -> void {
  visited[ix] = true;
  low[ix] = dfs[ix] = curr++;
  stack[++top] = ix;
  instack[ix] = true;
  for (auto edge : edges[ix]) {
    if (!visited[edge]) {
      tarjan(edge);
      low[ix] = std::min(low[ix], low[edge]);
    } else if (instack[edge]) {
      low[ix] = std::min(low[ix], dfs[edge]);
    }
  }
  if (low[ix] == dfs[ix]) {
    while (true) {
      auto el = stack[top];
      groupix[el] = currentGroup;
      instack[el] = false;
      auto &g = groups[currentGroup];
      // g.nodes += el;
      g.money += money[el];
      if (terminator[el]) g.terminator = true;
      --top;
      if (el == ix) break;
    }
    ++currentGroup;
  }
}

// int max = 0;
// auto fdfs (int gid, int parent, int curr) -> void {
//   auto &g = groups[gid];
//   if (g.maxHere >= curr) return;
//   g.maxHere = curr;
//   curr += g.money;
//   if (g.terminator) max = std::max(max, curr);
//   for (int x : g.nodes) {
//     for (int y : edges[x]) {
//       int yid = groupix[y];
//       if (gid == yid || parent == yid) continue;
//       fdfs(yid, gid, curr);
//     }
//   }
// }

int max = 0;
int queue[10 * kMaxn];
bool inqueue[10 * kMaxn];
si ge[kMaxn];
int begin = 0, end = 0;
auto enq (int x) -> void {
  queue[end++] = x;
  inqueue[x] = true;
}
auto deq () -> int {
  return queue[begin++];
}
auto empty () -> bool {
  return begin == end;
}
auto bfs (int gid) -> void {
  enq(gid);
  while (!empty()) {
    auto gidNow = deq();
    auto &group = groups[gidNow];
    auto moneyCurr = group.max + group.money;
    if (group.terminator) max = std::max(moneyCurr, max);
    for (auto gidEdge : ge[gidNow]) {
      auto &groupEdge = groups[gidEdge];
      if (moneyCurr > groupEdge.max) {
        groupEdge.max = moneyCurr;
      }
      if (!inqueue[gidEdge]) enq(gidEdge);
    }
    inqueue[gidNow] = false;
  }
}

auto main () -> int {
#ifdef DEBUG_VSCODE
  freopen("1197.in", "r", stdin);
#endif
  int n = nextInt(), m = nextInt();
  for (int i = 0; i < m; ++i) {
    int a = nextInt() - 1, b = nextInt() - 1;
    edges[a] += b;
  }
  for (int i = 0; i < n; ++i) {
    money[i] = nextInt();
  }
  int start = nextInt() - 1, p = nextInt();
  for (int i = 0; i < p; ++i) {
    terminator[nextInt() - 1] = true;
  }

  tarjan(start);
  for (int i = 0; i < n; ++i) {
    for (int j : edges[i]) {
      int a = groupix[i], b = groupix[j];
      if (a != b) ge[a] += b;
    }
  }
  bfs(groupix[start]);
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

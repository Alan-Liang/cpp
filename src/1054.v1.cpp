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

constexpr int kMaxn = 1e5 + 10;
using si = std::basic_string<int>;

si edges[kMaxn];
struct {
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
      g.max = std::max(g.max, el);
      --top;
      if (el == ix) break;
    }
    ++currentGroup;
  }
}

int indeg[kMaxn];
si gedges[kMaxn];
auto fillEdges (int n) {
  for (int i = 0; i < n; ++i) {
    for (int to : edges[i]) {
      if (groupix[i] == groupix[to]) continue;
      gedges[groupix[i]] += groupix[to];
      ++indeg[groupix[to]];
    }
  }
}

template <int max>
struct Queue {
  int queue[max];
  int inqueue[max];
  int begin, end;
  auto enq (int x) {
    if (inqueue[x]) return;
    inqueue[x] = true;
    queue[end++] = x;
  }
  auto deq () {
    int x = queue[begin++];
    inqueue[x] = false;
    return x;
  }
  auto empty () {
    return begin == end;
  }
};
Queue<kMaxn> q;
auto fill (int n) {
  for (int i = 0; i < n; ++i) {
    if (indeg[i] == 0) q.enq(i);
  }
  while (!q.empty()) {
    auto gid = q.deq();
    auto &g = groups[gid];
    for (auto to : gedges[gid]) {
      auto &g1 = groups[to];
      g1.max = std::max(g1.max, g.max);
      q.enq(to);
    }
  }
}

auto main () -> int {
  int n = nextInt(), m = nextInt();
  for (int i = 0; i < m; ++i) {
    int x = nextInt() - 1, y = nextInt() - 1;
    edges[y] += x;
  }
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) tarjan(i);
  }
  fillEdges(n);
  fill(currentGroup);
  for (int i = 0; i < n; ++i) {
    printsp(groups[groupix[i]].max + 1);
  }
  putchar('\n');
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

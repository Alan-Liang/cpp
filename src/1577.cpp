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

constexpr int kMaxn = 5e4 + 10;

struct Edge {
  int to, weight;
  int ixReverse;
  bool enabled;
};
std::basic_string<Edge> edges[kMaxn];
int n, m;

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
  auto clear () {
    begin = end = 0;
    // memset(inqueue, 0, sizeof(inqueue));
  }
};
Queue<100 * kMaxn> q;
int dist[kMaxn];
auto search () -> int {
  memset(dist, 0x7f, sizeof(dist));
  q.clear();
  q.enq(1);
  dist[1] = 0;
  while (!q.empty()) {
    int x = q.deq();
    for (auto &edge : edges[x]) {
      if (!edge.enabled) continue;
      if (dist[edge.to] > dist[x] + edge.weight) {
        dist[edge.to] = dist[x] + edge.weight;
        q.enq(edge.to);
      }
    }
  }
  return dist[0];
}

auto main () -> signed {
  n = nextInt(), m = nextInt();
  for (int i = 0; i < m; ++i) {
    int x = nextInt(), y = nextInt(), w1 = nextInt(), w2 = nextInt();
    if (y == 1) {
      std::swap(x, y);
      std::swap(w1, w2);
    }
    edges[x] += { y, w1, (int) edges[y].length(), true };
    if (x == 1) x = 0;
    edges[y] += { x, w2, (int) edges[x].length() - 1, true };
  }
  int min = 0x7f7f7f7f;
  for (int bit = 0; bit < 16; ++bit) {
    for (int i = 0; i < edges[1].length(); ++i) {
      auto &ed = edges[1][i];
      bool f = i & (1 << bit);
      ed.enabled = f;
      edges[ed.to][ed.ixReverse].enabled = !f;
    }
    min = std::min(min, search());

    for (int i = 0; i < edges[1].length(); ++i) {
      auto &ed = edges[1][i];
      bool f = i & (1 << bit);
      ed.enabled = !f;
      edges[ed.to][ed.ixReverse].enabled = f;
    }
    min = std::min(min, search());
  }
  println(min);

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

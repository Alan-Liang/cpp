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

constexpr int kMaxn = 1e3 + 10;

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
Queue<kMaxn * kMaxn> q;
struct Edge {
  int to;
  int weight;
};
std::basic_string<Edge> edges[kMaxn * kMaxn];
int dist[kMaxn * kMaxn];
auto spfa (int start) {
  q.enq(start);
  dist[start] = 0;
  while (!q.empty()) {
    int from = q.deq();
    // printf(">> ");
    // println(from);
    for (auto &edge : edges[from]) {
      auto curr = std::max(dist[from], edge.weight);
      // printsp(edge.to);
      // printsp(edge.weight);
      // printsp(dist[edge.to]);
      // println(curr);
      if (dist[edge.to] > curr) {
        dist[edge.to] = curr;
        q.enq(edge.to);
      }
    }
  }
}
auto edgeid (int i, int k) {
  return i * kMaxn + k;
}
auto add (int from, int to, int w) {
  edges[from] += (Edge){ to, w };
  edges[to] += (Edge){ from, w };
}
auto addFree (int from, int to, int k) {
  edges[edgeid(from, k)] += (Edge){ edgeid(to, k - 1), 0 };
  edges[edgeid(to, k)] += (Edge){ edgeid(from, k - 1), 0 };
}

auto main () -> int {
  int n = nextInt(), p = nextInt(), k = nextInt();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= k; ++j) {
      dist[edgeid(i, j)] = 0x7f7f7f7f;
    }
  }
  for (int i = 0; i < p; ++i) {
    int from = nextInt() - 1, to = nextInt() - 1, w = nextInt();
    add(edgeid(from, 0), edgeid(to, 0), w);
    for (int i = 1; i <= k; ++i) {
      add(edgeid(from, i), edgeid(to, i), w);
      addFree(from, to, i);
    }
  }
  spfa(edgeid(0, k));
  int min = 0x7f7f7f7f;
  for (int i = 0; i <= k; ++i) {
    min = std::min(min, dist[edgeid(n - 1, i)]);
  }
  if (min == 0x7f7f7f7f) println(-1);
  else println(min);
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

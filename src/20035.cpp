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
constexpr int kBits = 5;
#else
constexpr int kMaxn = 5e5 + 10;
constexpr int kBits = 12;
#endif
constexpr int pow2[] = { 1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12 };
auto getbit (int num, int n) -> int {
  return (pow2[n] & num) ? 1 : 0;
}
auto bitinv (int bit) -> int {
  return bit ? 0 : 1;
}
struct TrieNode {
  TrieNode *child[2] = {};
  auto insert (int num, int pos) -> void {
    if (pos < 0) return;
    int bit = getbit(num, pos);
    if (child[bit] == nullptr) child[bit] = new TrieNode;
    return child[bit]->insert(num, pos - 1);
  }
  auto query (int mask, int pos, int cumulative) -> int {
    if (pos < 0) return cumulative;
    int maskBit = getbit(mask, pos);
    int want = bitinv(maskBit);
    if (child[want] != nullptr) {
      return child[want]->query(mask, pos - 1, cumulative | pow2[pos]);
    } else {
      return child[maskBit]->query(mask, pos - 1, cumulative);
    }
  }
};
struct Trie {
  TrieNode root;
  auto insert (int num) -> void { root.insert(num, kBits - 1); }
  auto query (int mask) -> int { return root.query(mask, kBits - 1, 0); }
  auto batchInsert (bool *a, bool *b) -> void {
    for (int i = 0; i < (1 << kBits); ++i) if (a[i]) for (int j = 0; j < (1 << kBits); ++j) if (b[j]) {
      int val = i ^ j;
      insert(val);
    }
  }
};
Trie tconst, tvolatile;

struct Edge {
  int children;
  int weight;
};
using ca = std::basic_string<Edge>;
int parent[kMaxn];
int cumulativeWeight[kMaxn];
bool isNodeConst[kMaxn];
ca edges[kMaxn];

bool wconst[1 << kBits], wvolatile[1 << kBits];

auto dfs (int curr, int ixParent, int weightSelf, bool isConst) -> void {
  parent[curr] = ixParent;
  cumulativeWeight[curr] = weightSelf;
  isNodeConst[curr] = isConst;
  if (isConst) {
    wconst[weightSelf] = true;
  } else {
    wvolatile[weightSelf] = true;
  }
  for (auto [ child, weight ] : edges[curr]) {
    if (child == ixParent) continue;
    dfs(child, curr, weightSelf ^ weight, !isConst);
  }
}

auto main () -> int {
  int numNodes = nextInt(), numOps = nextInt();
  for (int i = 1; i < numNodes; ++i) {
    int x = nextInt(), y = nextInt(), w = nextInt();
    edges[x] += { y, w };
    edges[y] += { x, w };
  }
  dfs(1, 0, 0, true);
  tconst.batchInsert(wconst, wconst);
  tconst.batchInsert(wvolatile, wvolatile);
  tvolatile.batchInsert(wconst, wvolatile);
  int maskGlobal = 0;
  for (int i = 0; i < numOps; ++i) {
    int op = nextInt();
    if (op == 1) {
      int x = nextInt(), y = nextInt();
      int mask = isNodeConst[x] == isNodeConst[y] ? 0 : maskGlobal;
      int target = cumulativeWeight[x] ^ cumulativeWeight[y] ^ mask;
      int max = std::max(tconst.query(target), tvolatile.query(target ^ maskGlobal));
      println(max);
    } else {
      maskGlobal ^= nextInt();
    }
  }
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

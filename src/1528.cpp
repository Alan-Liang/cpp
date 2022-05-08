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
constexpr int kMaxn = 15;
#else
constexpr int kMaxn = 1e5 + 10;
#endif

enum LazyTag { kNone, kFill, kClear };
struct Node {
  int length = 0;
  int pre = 0;
  int post = 0;
  int max = 0;
  LazyTag lazy = kNone;
  auto operator+ (const Node &rhs) -> Node {
    int x1 = post + rhs.pre;
    int x2 = rhs.max;
    int x3 = max;
    int pre1 = pre == length ? pre + rhs.pre : pre;
    int post1 = rhs.post == rhs.length ? post + rhs.post : rhs.post;
    int len1 = length + rhs.length;
    return { len1, pre1, post1, std::max(std::max(x1, x2), x3), kNone };
  }
};
int array[kMaxn];
Node tree[4 * kMaxn];
auto pushup (int ix) -> void {
  tree[ix] = tree[ix * 2] + tree[ix * 2 + 1];
}
auto build (int left, int right, int root) -> void {
  if (left == right) {
    tree[root].length = tree[root].pre = tree[root].post = tree[root].max = 1;
    return;
  }
  int mid = (left + right) / 2;
  build(left, mid, root * 2);
  build(mid + 1, right, root * 2 + 1);
  pushup(root);
}
auto change (LazyTag type, int ix) -> void {
  auto &node = tree[ix];
  int has = type == kFill ? 0 : node.length;
  node.pre = node.post = node.max = has;
  node.lazy = type;
}
auto pushdown (int ix) -> void {
  auto &tag = tree[ix].lazy;
  if (tag == kNone) return;
  change(tag, ix * 2);
  change(tag, ix * 2 + 1);
  tag = kNone;
}
auto mod (LazyTag type, int left, int right, int ll, int rr, int ix) -> void {
  pushdown(ix);
  if (left <= ll && right >= rr) {
    change(type, ix);
    return;
  }
  int mid = (ll + rr) / 2;
  if (left <= mid) mod(type, left, right, ll, mid, ix * 2);
  if (right > mid) mod(type, left, right, mid + 1, rr, ix * 2 + 1);
  pushup(ix);
}
auto query (int target, int ll, int rr, int ix) -> int {
  pushdown(ix);
  if (ll == rr) return ll;
  int mid = (ll + rr) / 2;
  if (tree[ix * 2].max >= target) return query(target, ll, mid, ix * 2);
  if (tree[ix * 2].post + tree[ix * 2 + 1].pre >= target) {
    return mid - tree[ix * 2].post + 1;
  }
  return query(target, mid + 1, rr, ix * 2 + 1);
}

auto main () -> int {
  int numNodes = nextInt(), numOps = nextInt();
  build(0, numNodes - 1, 1);
  for (int i = 0; i < numOps; ++i) {
    int op = nextInt();
    if (op == 1) {
      int length = nextInt();
      if (tree[1].max < length) {
        println('0');
        continue;
      }
      int ix = query(length, 0, numNodes - 1, 1);
      println(ix + 1);
      mod(kFill, ix, ix + length - 1, 0, numNodes - 1, 1);
    } else {
      int offset = nextInt() - 1, count = nextInt();
      mod(kClear, offset, offset + count - 1, 0, numNodes - 1, 1);
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

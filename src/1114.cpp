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
constexpr int numLetters = 5;
#else
constexpr int kMaxn = 2e5 + 10;
constexpr int numLetters = 26;
#endif

enum LazyTag { kNone, kAsc, kDesc };
struct Letters {
  int count[numLetters] = {};
  auto operator[] (int i) -> int & { return count[i]; }
  auto operator[] (int i) const -> const int & { return count[i]; }
  auto operator+ (const Letters &rhs) -> Letters {
    Letters res;
    for (int i = 0; i < numLetters; ++i) {
      res.count[i] = count[i] + rhs.count[i];
    }
    return res;
  }
};
struct Node {
  int length = 1;
  Letters count;
  LazyTag lazy = kNone;
  auto operator+ (const Node &rhs) -> Node {
    return { length + rhs.length, count + rhs.count, kNone };
  }
};
Node tree[4 * kMaxn];
char buf[kMaxn];
auto pushup (int ix) -> void {
  tree[ix] = tree[ix * 2] + tree[ix * 2 + 1];
}
auto build (int left, int right, int root) -> void {
  if (left == right) {
    tree[root].count[buf[left] - 'a'] = 1;
    return;
  }
  int mid = (left + right) / 2;
  build(left, mid, root * 2);
  build(mid + 1, right, root * 2 + 1);
  pushup(root);
}
auto change (LazyTag type, int ix) -> void {
  auto &node = tree[ix];
  if (node.length == 1) return;
  int count = 0;
  auto &left = tree[ix * 2];
  auto &right = tree[ix * 2 + 1];
  int i = 0;
  for (; i < numLetters; ++i) {
    int ix = type == kAsc ? i : numLetters - i - 1;
    count += node.count[ix];
    if (count >= left.length) {
      left.count[ix] = node.count[ix] - count + left.length;
      right.count[ix] = count - left.length;
      ++i;
      break;
    }
    left.count[ix] = node.count[ix];
    right.count[ix] = 0;
  }
  count = 0;
  for (; i < numLetters; ++i) {
    int ix = type == kAsc ? i : numLetters - i - 1;
    count += node.count[ix];
    if (count >= right.length) {
      right.count[ix] = node.count[ix] - count + right.length;
      left.count[ix] = 0;
      ++i;
      break;
    }
    right.count[ix] = node.count[ix];
    left.count[ix] = 0;
  }
  for (; i < numLetters; ++i) {
    int ix = type == kAsc ? i : numLetters - i - 1;
    left.count[ix] = right.count[ix] = 0;
  }
  node.lazy = type;
}
auto pushdown (int ix) -> void {
  auto &tag = tree[ix].lazy;
  if (tag == kNone) return;
  change(tag, ix * 2);
  change(tag, ix * 2 + 1);
  tag = kNone;
}
auto mod (Letters &args, LazyTag type, int left, int right, int ll, int rr, int ix) -> void {
  if (left <= ll && right >= rr) {
    auto &node = tree[ix];
    int i = 0;
    int count = 0;
    for (; i < numLetters; ++i) {
      int ix = type == kAsc ? i : numLetters - i - 1;
      count += args[ix];
      if (count >= node.length) {
        node.count[ix] = args[ix] - count + node.length;
        args[ix] = count - node.length;
        ++i;
        break;
      }
      node.count[ix] = args[ix];
      args[ix] = 0;
    }
    for (; i < numLetters; ++i) {
      int ix = type == kAsc ? i : numLetters - i - 1;
      node.count[ix] = 0;
    }
    change(type, ix);
    return;
  }
  pushdown(ix);
  int mid = (ll + rr) / 2;
  if (left <= mid) mod(args, type, left, right, ll, mid, ix * 2);
  if (right > mid) mod(args, type, left, right, mid + 1, rr, ix * 2 + 1);
  pushup(ix);
}
auto query (int left, int right, int ll, int rr, int ix) -> Letters {
  if (left <= ll && right >= rr) return tree[ix].count;
  pushdown(ix);
  int mid = (ll + rr) / 2;
  if (right <= mid) return query(left, right, ll, mid, ix * 2);
  if (left > mid) return query(left, right, mid + 1, rr, ix * 2 + 1);
  return query(left, right, ll, mid, ix * 2) + query(left, right, mid + 1, rr, ix * 2 + 1);
}
auto dfs (int ll, int rr, int ix) -> void {
  if (ll == rr) {
    auto &node = tree[ix];
    for (int i = 0; i < numLetters; ++i) {
      if (node.count[i] > 0) {
        putchar(i + 'a');
        return;
      }
    }
    throw 1;
  }
  pushdown(ix);
  int mid = (ll + rr) / 2;
  dfs(ll, mid, ix * 2);
  dfs(mid + 1, rr, ix * 2 + 1);
}

auto main () -> int {
  int length = nextInt(), numOps = nextInt();
  scanf("%s", buf);
  build(0, length - 1, 1);
  for (int i = 0; i < numOps; ++i) {
    int left = nextInt() - 1, right = nextInt() - 1, op = nextInt();
    Letters args = query(left, right, 0, length - 1, 1);
#ifdef DEBUG
    for (int i = 0; i < numLetters; ++i) for (int j = 0; j < args[i]; ++j) putchar(i + 'a');
    putchar('\n');
#endif
    mod(args, op == 0 ? kDesc : kAsc, left, right, 0, length - 1, 1);
#ifdef DEBUG
    dfs(0, length - 1, 1);
    putchar('\n');
#endif
  }
  dfs(0, length - 1, 1);
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

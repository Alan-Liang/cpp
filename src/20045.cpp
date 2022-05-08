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

constexpr int kMaxn = 4e5 + 10;
int array[kMaxn];
constexpr int kBits = 30;
constexpr int pow2[] = { 1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7, 1 << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16, 1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 21, 1 << 22, 1 << 23, 1 << 24, 1 << 25, 1 << 26, 1 << 27, 1 << 28, 1 << 29, 1 << 30 };
auto getbit (int n, int bit) -> int { return (n & pow2[bit]) == 0 ? 0 : 1; }

struct TrieNode {
  TrieNode *children[2] = {};
  static TrieNode pool[16 * kMaxn];
  static int next;
  static auto get () -> TrieNode * {
    TrieNode *res = &pool[next++];
    if (next > 16 * kMaxn) exit(0);
    new(res) TrieNode;
    return res;
  }
  auto insert (int num, int depth) -> void {
    if (depth < 0) return;
    int bit = getbit(num, depth);
    if (children[bit] == nullptr) {
      children[bit] = get();
    }
    return children[bit]->insert(num, depth - 1);
  }
  auto query (int mask, int depth, int current) -> int {
    if (depth < 0) return current;
    int bit = getbit(mask, depth);
    int target = bit == 0 ? 1 : 0;
    if (children[target] == nullptr) {
      return children[bit]->query(mask, depth - 1, current);
    } else {
      return children[target]->query(mask, depth - 1, current | pow2[depth]);
    }
  }
};
TrieNode TrieNode::pool[];
int TrieNode::next = 0;

template <typename T>
auto scan (T begin, T end, int *res) -> void {
  int i = 1;
  auto root = TrieNode::get();
  root->insert(0, kBits - 1);
  int current = 0;
  while (begin != end) {
    current ^= *begin;
    res[i] = std::max(res[i - 1], std::max(current, root->query(current, kBits - 1, 0)));
    root->insert(current, kBits - 1);
    ++i;
    ++begin;
  }
  TrieNode::next = 0;
}

int normal[kMaxn], reverse[kMaxn];

auto main () -> int {
  int n = nextInt();
  readN(array, n);
  std::basic_string_view<int> sv(array, n);
  scan(sv.begin(), sv.end(), normal);
  scan(sv.rbegin(), sv.rend(), reverse);
  int max = 0;
  for (int i = 1; i < n; ++i) {
    max = std::max(max, normal[i] + reverse[n - i]);
  }
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

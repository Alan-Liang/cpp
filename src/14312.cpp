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

int length;
const int kMaxn = 5000 + 10;
int prefix[kMaxn], infix[kMaxn];

struct Node {
  Node *left;
  Node *right;
  int value;
};

auto scan (int l1, int l2, int span) -> Node * {
  if (span == 0) return nullptr;
  int rootValue = prefix[l1];
  Node *root = new Node { nullptr, nullptr, rootValue };
  for (int i = 0; i < span; ++i) {
    if (infix[l2 + i] == rootValue) {
      root->left = scan(l1 + 1, l2, i);
      root->right = scan(l1 + 1 + i, l2 + i + 1, span - i - 1);
    }
  }
  return root;
}

auto printRoot (Node *root) -> void {
  if (root->left != nullptr) printRoot(root->left);
  if (root->right != nullptr) printRoot(root->right);
  printsp(root->value);
}

auto main () -> int {
  length = nextInt();
  readN(prefix, length);
  readN(infix, length);
  prefix[length] = infix[length] = kMaxn;
  printRoot(scan(0, 0, length));
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

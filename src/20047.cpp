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
constexpr int kChars = 26;

struct TrieNode;
TrieNode *root;
struct TrieNode {
  TrieNode *children[kChars] = {};
  TrieNode *fail = nullptr;
  bool isTerminator = false;
  auto insert (const char *str) -> void {
    if (!isalpha(*str)) {
      isTerminator = true;
      return;
    }
    int c = *str - 'a';
    if (children[c] == nullptr) children[c] = new TrieNode;
    return children[c]->insert(str + 1);
  }
  auto makeFail () -> void {
    for (int i = 0; i < kChars; ++i) {
      if (children[i] == nullptr) continue;
      if (this == root) {
        children[i]->fail = root;
        continue;
      }
      auto prev = fail;
      while (prev != root && prev->children[i] == nullptr) {
        prev = prev->fail;
      }
      if (prev->children[i] != nullptr) {
        children[i]->fail = prev->children[i];
        if (prev->children[i]->isTerminator) {
          children[i]->isTerminator = true;
        }
      } else {
        children[i]->fail = root;
      }
    }
  }
};

constexpr int kMaxc = 1e6 + 10;
char strings[kMaxc + kMaxn * 2];
char self[kMaxc];
int stringOffsets[kMaxn];
TrieNode *queue[kMaxc];
auto makeTrie (int numStrings) -> void {
  root = new TrieNode;
  for (int i = 0; i < numStrings; ++i) {
    root->insert(strings + stringOffsets[i]);
  }
  root->fail = root;
  int queueStart = 0;
  int queueEnd = 0;
  auto push = [&queueEnd] (TrieNode *node) { queue[queueEnd++] = node; };
  auto pop = [&queueStart] { return queue[queueStart++]; };
  push(root);
  while (queueStart < queueEnd) {
    TrieNode *current = pop();
    current->makeFail();
    for (auto child : current->children) {
      if (child != nullptr) push(child);
    }
  }
}

auto query () -> bool {
  int len = strlen(self);
  TrieNode *curr = root;
  for (int i = 0; i < len; ++i) {
    if (curr->isTerminator) return true;
    if (!isalpha(self[i])) continue;
    int c = self[i] - 'a';
    while (curr->children[c] == nullptr && curr != root) {
      curr = curr->fail;
    }
    curr = curr->children[c];
    if (curr == nullptr) curr = root;
  }
  return false;
}

auto main () -> int {
  int numStrings = nextInt();
  int offset = 0;
  int szBuf = sizeof(strings) / sizeof(strings[0]);
  for (int i = 0; i < numStrings; ++i) {
    stringOffsets[i] = offset;
    fgets(strings + offset, szBuf, stdin);
    offset += strlen(strings + offset) + 1;
  }
  fgets(self, sizeof(self), stdin);
  makeTrie(numStrings);
  println(query() ? "valar morghulis" : "valar dohaeris");
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

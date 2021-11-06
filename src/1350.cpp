#include <bits/stdc++.h>

using namespace std;

#undef strcspn
#undef strstr

namespace panic {
size_t strlen (const char *str) {
  int length = 0;
  while (str[length++]) {}
  return length - 1;
}
}

/**
 * @brief "Complementary SPaN"：返回s中第一个未出现在字符串reject中的字符的下标。
 * @param s 源字符串
 * @param reject 一个字符串，包含不允许出现的字符
 * @return 如果存在s中的字符，且其未出现在reject串中，返回第一个这样的字符的下标；否则返回s的长度。
 */
size_t strcspn (const char *self, const char *reject) {
  size_t lenReject = panic::strlen(reject);
  size_t lenSelf = panic::strlen(self);
  size_t i = 0;
  next:
  if (i == lenSelf) return i;
  for (size_t j = 0; j < lenReject; ++j) {
    if (self[i] == reject[j]) {
      ++i;
      goto next;
    }
  }
  return i;
}

/**
 * @brief 查找字符串needle在haystack中第一次出现的位置
 * @param haystack 目标字符串
 * @param src 源字符串
 * @return 返回第一次出现的位置，如果未出现返回空指针
 * @par 时间复杂度O(N * M) 即可，其中N、M分别为haystack和needle的长度。
 * glibc的实现采用了Knuth-Morris-Pratt算法，这是一个O(N + M) 的字符串匹配算法。它的实现见 <https://github.com/jeremie-koenig/glibc/blob/master-beware-rebase/sysdeps/x86_64/multiarch/strstr.c>。
 */
char *strstr (char *self, const char *find) {
  size_t lenSelf = panic::strlen(self);
  size_t lenFind = panic::strlen(find);
  if (lenFind == 0) return self;
  if (lenSelf < lenFind) return nullptr;
  int offset = 0;
  next:
  if (offset + lenFind > lenSelf) return nullptr;
  for (int i = 0; i < lenFind; ++i) {
    if (self[offset + i] != find[i]) {
      ++offset;
      goto next;
    }
  }
  return self + offset;
}

//---------------------------------------
int n;
int main () {
  ios::sync_with_stdio(0), cin.tie(0);

  string s1, s2;
  int op;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> op >> s1 >> s2;
    if (op == 1) {
      cout << strcspn(s1.c_str(), s2.c_str()) << '\n';
    } else if (op == 2) {
      const char *res = strstr(s1.c_str(), s2.c_str());
      if (res == nullptr) cout << "NOT FOUND\n";
      else cout << res << '\n';
    }
  }

  return 0;
}

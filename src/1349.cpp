#include <bits/stdc++.h>

using namespace std;

#undef strcmp
#undef strcpy

/**
 * @brief 比较两个字符串, not timing-safe
 * @param s1 一个字符串
 * @param s2 一个字符串
 * @return 按字典序比较字符串. 如果 s1 < s2, 返回 -1; 如果 s1 == s2. 返回 0; 如果 s1 > s2, 返回 1.
 */
int strcmp (const char *s1, const char *s2) {
  for (int i = 0;; ++i) {
    const char &char1 = s1[i];
    const char &char2 = s2[i];
    if (char1 == '\0' && char2 == '\0') return 0;
    if (char1 == '\0') return -1;
    if (char2 == '\0') return 1;
    if (char1 != char2) return (char1 < char2) ? -1 : 1;
  }
}

namespace panic {
size_t strlen (const char *str) {
  int length = 0;
  while (str[length++]) {}
  return length - 1;
}
}

/**
 * @brief 复制 src 字符串到 dest
 * @param dest 目标字符串
 * @param src 源字符串
 * @return dest 指针
 * @par 关键字 `__restrict` 的作用是要求传入的 `dest` 和 `src` 之间没有重叠, 具体可以参考 <https://en.cppreference.com/w/c/language/restrict>
 * 在本题中, 如果复制会导致 `dest` 与 `src` 有重叠 (`dest` 在前, `src` 在后; 或者 `src` 在前, `dest` 在后), 请什么都不做, 然后返回 `dest`. 这点与标准库中不同.
 */
char* strcpy (char * __restrict dest, const char * __restrict src) {
  if (src == dest) return dest;
  size_t lenSrc = panic::strlen(src);
  bool overlapDestSrc = dest < src && (dest + lenSrc) >= src;
  bool overlapSrcDest = src < dest && (src + lenSrc) >= dest;
  bool overlap = overlapDestSrc || overlapSrcDest;
  if (overlap) return dest;
  for (int i = 0; i <= lenSrc; ++i) dest[i] = src[i];
  return dest;
}

int n;
int main () {
  ios::sync_with_stdio(0),cin.tie(0);

  string s1, s2;
  int op;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> op >> s1;
    if (op == 1) {
      cin >> s2;
      cout << strcmp(s1.c_str(), s2.c_str()) << '\n';
    } else if (op == 2) {
      char *arr = new char[s1.length() + 1];
      cout << strcpy(arr, s1.c_str()) << '\n';
      delete[] arr;
    } else if (op == 3) {
      //s1 shouldn't be too short
      char *arr = new char[s1.length() * 2 + 1];
      arr[0] = 'w';
      arr[1] = '\0';
      const char *tmp = s1.c_str();
      char *to = arr + s1.length();
      while(*tmp) {
        *to = *tmp;
        ++to, ++tmp;
      }
      *to = 0;
      cout << strcpy(arr, arr + s1.length()) << '\n';
      delete[] arr;
    } else if (op == 4) {
      cout << strcpy((char*)s1.c_str() + s1.length() - 3, s1.c_str()) << '\n';
    }
  }
  return 0;
}

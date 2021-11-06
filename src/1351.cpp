#include <bits/stdc++.h>

#undef strtok

namespace panic {

size_t strlen (const char *str) {
  int length = 0;
  while (str[length++]) {}
  return length - 1;
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

size_t strspn (const char *self, const char *accept) {
  size_t lenAccept = panic::strlen(accept);
  size_t lenSelf = panic::strlen(self);
  for (size_t i = 0; i < lenSelf; ++i) {
    for (size_t j = 0; j < lenAccept; ++j) {
      if (self[i] == accept[j]) return i;
    }
  }
  return lenSelf;
}

} // namespace panic

char *strtok (char *__restrict self, const char *__restrict delim) {
  static char *__restrict self_;
  if (self != nullptr) {
    // If str is not a null pointer, the call is treated as the first call to strtok for this particular string.
    size_t lenSelf = panic::strlen(self);
    size_t lenDelim = panic::strlen(delim);
    // The function searches for the first character which is not contained in delim.
    size_t ix = panic::strcspn(self, delim);
    // If no such character was found, there are no tokens in str at all, and the function returns a null pointer.
    if (ix == lenSelf) return nullptr;
    // If such character was found, it is the beginning of the token. The function then searches from that point on for the first character that is contained in delim.
    size_t offset = panic::strspn(self + ix, delim);
    // If no such character was found, str has only one token, and future calls to strtok will return a null pointer
    if (offset == lenSelf - ix) self_ = nullptr;
    // If such character was found, it is replaced by the null character '\0' and the pointer to the following character is stored in a static location for subsequent invocations.
    if (offset != lenSelf - ix) {
      self[ix + offset] = '\0';
      self_ = self + ix + offset + 1;
    }
    // The function then returns the pointer to the beginning of the token.
    return self + ix;
  } else {
    // If str is a null pointer, the call is treated as a subsequent calls to strtok: the function continues from where it left in previous invocation. The behavior is the same as if the previously stored pointer is passed as str.
    if (self_ == nullptr) return nullptr;
    return strtok(self_, delim);
  }
}

using namespace std;

//---------------------------------------
int n;
char s1[2000000], s2[100];
int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  int op;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> op >> s1 >> s2;
    char *token = strtok(s1, s2);
      while(token != nullptr) {
      if (*token == '\0') cout << "empty str\n";
      else cout << token << '\n';
      token = strtok(nullptr, s2);
      }
  }

  return 0;
}

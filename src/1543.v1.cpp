#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

#ifdef DEBUG
constexpr int kMaxn = 10;
#else
constexpr int kMaxn = 2e5 + 10;
#endif
auto nextInt () -> int {
    char ch = getchar(); 
    int x = 0, f = 1;
    while(ch < '0' || ch > '9') 
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9') 
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    } 
    return x * f;
}
int array[kMaxn];
auto main () -> int {
  int n = nextInt();
  for (int i = 0; i < n; ++i) array[i] = nextInt();
  ;
  return 0;
}

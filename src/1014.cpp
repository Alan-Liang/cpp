#include <iostream>
#include <cmath>

#define loopfrom(n,i,f) for(int i=f;i<n;i++)
#define loop(n,i) loopfrom(n,i,0)
#define sgn(x) ((x)>0?1:(x)==0?0:-1)

#ifdef ONLINE_JUDGE
#define debug 
#else
#define debug std::cout << "[DEBUG]"; loop (len, __loop_var_debug) std::cout << " " << a[__loop_var_debug]; std::cout << "\n";
#endif

#define MAXN 100001

int len;
int a[MAXN], delta[MAXN];

void read () {
  std::ios_base::sync_with_stdio(false);
  std::cin >> len;
  loop (len, i) std::cin >> a[i];
  loop (len, i) {
    int b_i;
    std::cin >> b_i;
    a[i] -= b_i;
  }
  int j = 0;
  loop (len, i) {
    if (a[i] != 0) delta[j++] = a[i];
  }
  len = j + 1;
  debug
}

int calc () {
  int ins_count = abs(delta[0]);
  int current_sign = sgn(delta[0]);
  loop (len - 1, i) {
    if (sgn(delta[i + 1]) != sgn(delta[i])) {
      ins_count += abs(delta[i + 1]);
      current_sign = sgn(delta[i + 1]);
      continue;
    }
    if (sgn(delta[i + 1] - delta[i]) == current_sign) ins_count += abs(delta[i + 1] - delta[i]);
  }
  return ins_count;
}

int main () {
  read();
  std::cout << calc() << std::endl;
}

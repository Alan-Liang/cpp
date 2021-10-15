#include <iostream>
using namespace std;

int main () {
  unsigned long long current, dividend, delta1, delta2, start, ans = 0;
  cin >> current >> dividend >> delta1 >> delta2;
  start = current;
  if (dividend == 1 && current != 1) {
    cout << (current - 1) * delta1 << endl;
    return 0;
  }
  if (current == 1) {
    cout << 0 << endl;
    return 0;
  }

  while (current > dividend) {
    unsigned long long remainder = current % dividend;
    if (remainder > 0) {
      ans += delta1 * remainder;
      current -= remainder;
    } else {
      if ((current - current / dividend) * delta1 < delta2) {
        ans += delta1 * (current - 1);
        cout << ans << endl;
        return 0;
      }
      ans += delta2;
      current /= dividend;
    }
  }
  if (current == dividend) ans += min(delta2, (current - 1) * delta1);
  else ans += (current - 1) * delta1;
  cout << min(ans, (start - 1) * delta1) << endl;
  return 0;
}

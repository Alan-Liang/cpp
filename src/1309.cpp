#include <iostream>

#define MAXN 1000001

using std::cin, std::cout, std::endl;

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int length;
  cin >> length;
  int max = 0;
  int current = 0;
  for (int i = 0; i < length; ++i) {
    int num;
    cin >> num;
    if (current > 0) {
      current += num;
    } else {
      current = num;
    }
    if (max < current) max = current;
  }
  cout << max << endl;

  return 0;
}

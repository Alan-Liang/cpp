#include <algorithm>
#include <iostream>
#include <string>

using std::cin, std::cout, std::endl;

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  std::string str;
  int k;
  cin >> str >> k;
  std::sort(str.begin(), str.end());
  for (int i = 0; i < k - 1; ++i) std::next_permutation(str.begin(), str.end());
  cout << str << endl;
  return 0;
}

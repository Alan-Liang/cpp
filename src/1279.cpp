#include <cstring>
#include <algorithm>
#include <iostream>

using std::cin, std::cout, std::endl;

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int numQueries;
  cin >> numQueries;
  for (int i = 0; i < numQueries; ++i) {
    int length;
    cin >> length;
    char str[length + 1], sorted[length + 1];
    cin >> str;
    memcpy(sorted, str, sizeof(str));
    std::sort(sorted, sorted + length);
    int movesNeeded = 0;
    for (int j = 0; j < length; ++j) {
      if (str[j] != sorted[j]) ++movesNeeded;
    }
    cout << movesNeeded << '\n';
  }
  return 0;
}

#include <cstring>
#include <iostream>
#include <set>

using std::cin, std::cout, std::endl;

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int numNumbers, numQueries;
  cin >> numNumbers >> numQueries;
  int numbers[numNumbers];
  for (int i = 0; i < numNumbers; ++i) cin >> numbers[i];

  for (int i = 0; i < numQueries; ++i) {
    int numQueryNumbers;
    cin >> numQueryNumbers;
    std::set<int> queryNumbers;
    for (int j = 0; j < numQueryNumbers; ++j) {
      int numberOfQuery;
      cin >> numberOfQuery;
      queryNumbers.insert(numberOfQuery);
    }

    std::set<int> ok;
    int numWanted = queryNumbers.size();
    int upperBound = 0, lowerBound = -1;
    int minSize = numNumbers + 1;
    while (true) {
      while (true) {
        int num = numbers[upperBound];
        if (queryNumbers.count(num) > 0) ok.insert(num);
        if (ok.size() == numWanted) break;
        if (upperBound == numNumbers - 1) goto final;
        ++upperBound;
      }
      ok.clear();

      lowerBound = upperBound;
      while (true) {
        int num = numbers[lowerBound];
        if (queryNumbers.count(num) > 0) ok.insert(num);
        if (ok.size() == numWanted) break;
        --lowerBound;
      }
      int size = upperBound - lowerBound + 1;
      if (size < minSize) minSize = size;
      upperBound = lowerBound + 1;
      if (upperBound >= numNumbers) goto final;
      ok.clear();
    }
    final:
    cout << minSize << endl;
  }

  return 0;
}

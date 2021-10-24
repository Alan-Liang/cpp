#include <algorithm>
#include <iostream>
#include <set>

using std::cin, std::cout, std::endl;

constexpr int MAXLEN = 1001;

struct Cow {
  Cow () {}
  Cow (int size) : size(size), id(MAXLEN + 1), weight(-1), height(-1) {}

  int id;
  int height;
  int weight;
  int size;

  bool operator< (const Cow &that) const {
    if (size != that.size) return size < that.size;
    return id < that.id;
  }
};

Cow cows[MAXLEN];

class sortCowIndexByWeightReverse {
 public:
  bool operator() (const int &lhs, const int &rhs) const {
    if (cows[lhs].weight != cows[rhs].weight) return cows[lhs].weight > cows[rhs].weight;
    return cows[lhs].id < cows[rhs].id;
  }
};

int main () {
#ifdef ONLINE_JUDGE
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
#endif
#ifdef DEBUG_VSCODE
  freopen("1372.in", "r", stdin);
#endif

  int length, a, b, c;
  cin >> length >> a >> b >> c;
  std::set<int> heights;
  for (int i = 0; i < length; ++i) {
    int height, weight;
    cin >> height >> weight;
    heights.insert(height);
    cows[i].size = a * height + b * weight;
    cows[i].weight = weight;
    cows[i].height = height;
    cows[i].id = i;
  }
  std::sort(cows, cows + length);
  std::set<Cow> cowset;
  for (int i = 0; i < length; ++i) {
    cows[i].id = i;
    cowset.emplace(cows[i]);
  }

  int maxCowsAvailable = -1;
  for (const int minHeight : heights) {
    std::set<int, sortCowIndexByWeightReverse> cowsHeightOkByWeightDesc;
    std::set<int> cowsOk;
    for (const Cow &cow : cowset) {
      if (cow.height >= minHeight) cowsHeightOkByWeightDesc.insert(cow.id);
    }

    for (const int cowIndexOfMinWeight : cowsHeightOkByWeightDesc) {
      const int minWeight = cows[cowIndexOfMinWeight].weight;
      const int maxSize = c + a * minHeight + b * minWeight;
      cowsOk.insert(cowIndexOfMinWeight);
      const auto lastOk = cowset.upper_bound(maxSize);
      if (lastOk != cowset.end()) {
        const auto firstCowToRemove = cowsOk.lower_bound(lastOk->id);
        if (firstCowToRemove != cowsOk.end()) {
          cowsOk.erase(firstCowToRemove, cowsOk.end());
        }
      }
      const int currentSize = cowsOk.size();
      if (currentSize > maxCowsAvailable) maxCowsAvailable = currentSize;
    }
  }
  cout << maxCowsAvailable << endl;

  return 0;
}

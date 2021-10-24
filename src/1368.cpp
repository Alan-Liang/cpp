#include <cstring>
#include <algorithm>
#include <iostream>

using std::cin, std::cout, std::endl;

struct Tree {
 public:
  int initial;
  int velocity;

  int getValue (int day) {
    return initial + velocity * (day - 1);
  }

  bool operator< (const Tree &that) const {
    return velocity < that.velocity;
  }
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
#ifdef DEBUG_VSCODE
  freopen("1368.in", "r", stdin);
#endif

  int numTrees, days;
  cin >> numTrees >> days;
  Tree trees[numTrees + 1];
  for (int i = 1; i <= numTrees; ++i) cin >> trees[i].initial;
  for (int i = 1; i <= numTrees; ++i) cin >> trees[i].velocity;
  if (numTrees < days) {
    int delta = days - numTrees;
    for (int i = 1; i <= numTrees; ++i) trees[i].initial += trees[i].velocity * delta;
    days = numTrees;
  }
  std::sort(trees + 1, trees + numTrees + 1);

  int dp[numTrees + 1][days + 1];
  memset(dp, 0, sizeof(dp));
  for (int day = 1; day <= days; ++day) {
    for (int treeId = 1; treeId <= numTrees; ++treeId) {
      dp[treeId][day] = std::max(
        dp[treeId - 1][day - 1] + trees[treeId].getValue(day),
        dp[treeId - 1][day]
      );
    }
  }

  int max = -1;
  for (int i = 1; i <= numTrees; ++i) {
    if (dp[i][days] > max) max = dp[i][days];
  }

  cout << max << endl;

  return 0;
}

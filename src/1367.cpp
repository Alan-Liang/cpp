#include <algorithm>
#include <vector>
#include <iostream>

using std::cin, std::cout, std::endl;

#define int unsigned long long

signed main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int length;
  cin >> length;

  // strategy 2 requires at least 2 person
  if (length == 1) {
    int a;
    cin >> a;
    cout << a << endl;
    return 0;
  }

  std::vector<int> times;
  times.reserve(length);
  for (int i = 0; i < length; ++i) {
    int time;
    cin >> time;
    times.push_back(time);
  }
  std::sort(times.begin(), times.end());

  int fastest = times[0];
  int slightlySlower = times[1];
  int totalTime = 0;
  while (times.size() >= 4) {
    int slowest = times.back();
    times.pop_back();
    int slightlyFaster = times.back();
    times.pop_back();

    if (slightlySlower * 2 >= slightlyFaster + fastest) {
      for (const int &time : times) {
        totalTime += time;
        totalTime += fastest;
      }
      totalTime -= 2 * fastest;
      totalTime += (slowest + fastest + slightlyFaster);
      cout << totalTime << endl;
      return 0;
    }

    totalTime += (2 * slightlySlower + fastest + slowest);
  }

  if (times.size() == 3) {
    totalTime += (times[2] + fastest + slightlySlower);
  } else { // times.size() == 2
    totalTime += slightlySlower;
  }

  cout << totalTime << endl;

  return 0;
}
#undef int

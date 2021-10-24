#include <iostream>
#include <queue>

using std::cin, std::cout, std::endl;

typedef unsigned long long num_t;

class greaterThan {
 public:
  bool operator() (const num_t &lhs, const num_t &rhs) const {
    return lhs > rhs;
  }
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  num_t length;
  cin >> length;
  std::priority_queue<num_t, std::vector<num_t>, greaterThan> remains;
  for (num_t i = 0; i < length; ++i) {
    num_t num;
    cin >> num;
    remains.push(num);
  }
  num_t result = 0;
  while (remains.size() > 1) {
    num_t a, b;
    a = remains.top();
    remains.pop();
    b = remains.top();
    remains.pop();
    num_t sum = a + b;
    remains.push(sum);
    result += sum;
  }
  cout << result << endl;
  return 0;
}

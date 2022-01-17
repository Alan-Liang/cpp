#include <iostream>
#include <vector>
#include <functional>

auto getCounter () {
  static std::vector<int> counts;
  int id = counts.size();
  counts.push_back(0);
  return [=] () -> int {
    return counts[id]++;
  };
}

void put (int i) {
  std::cout << i << std::endl;
}

void execute (std::function<void (void)> func) {
  func();
}

int main () {
  int a;
  std::cin >> a;
  execute([&] { std::cout << a << std::endl; });
  return 0;

  auto counter = getCounter();
  auto counter2 = getCounter();
  put(counter()); // 0
  put(counter2()); // 0
  put(counter()); // 1
  put(counter()); // 2
  put(counter2()); // 1
}

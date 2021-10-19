#include<iostream>

int main () {
  int m, time, daytime;
  time = daytime = 0;
  std::cin >> m;
  for (int i = 0; i < m; i++) {
    int interval;
    std::cin >> interval;
    if (interval > 13) {
      std::cout << "you died\n";
      break;
    }
    time += interval;
    if (daytime + interval > 13) {
      // zzz
      time += (20 - daytime);
      daytime = 0;
    }
    daytime += interval;
  }
  std::cout << time << std::endl;
}

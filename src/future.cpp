#include <iostream>
#include <future>
#include <thread>
#include <chrono>

auto wait (int sec) -> int {
  std::this_thread::sleep_for(std::chrono::seconds(sec));
  return sec;
}

auto mian () -> int {
  for (int i : { 0, 4, 5, 6 }) {
    std::cout << wait(i) << std::endl;
  }
  return 0;
}

auto main () -> int {
  std::future<int> ps[] = {
    std::async(wait, 0),
    std::async(wait, 7000),
    std::async(wait, 6000),
    std::async(wait, 5000),
    std::async(wait, 4000),
  };
  for (auto &p : ps) {
    p.wait();
    std::cout << p.get() << std::endl;
  }
  return 0;
}

#include <iostream>

using std::cin, std::cout, std::endl, std::clog;

int interval;

struct State {
  int count;
  int current;
  enum {
    kForward = 1,
    kBack = -1,
  } direction;

  State (int count) : count(count), current(1), direction(kBack) {}

  auto normalizedInterval () -> int {
    return interval % (2 * count - 2);
  }

  auto normalize () -> void {
    if (count == 1) return;
    if (current < 0) {
      current = -current;
      direction = kForward;
      normalize();
    }
    if (current >= count) {
      current = 2 * count - current - 2;
      direction = kBack;
      normalize();
    }
  }

  auto advance () -> void {
    current += direction * normalizedInterval();
    normalize();
  }

  auto rewind () -> int {
    --count;
    if (direction == kForward) {
      if (current == count) --current;
      current -= direction;
      normalize();
    } else if (current == 0) ++current;
    return pick();
  }

  auto pick () -> int {
    if (count == 1) return 0;
    advance();
    int prev = State(*this).rewind();
#ifdef DEBUG
    clog << ">> " << count << ' ' << current << ' ' << direction << ' ' << prev << endl;
#endif
    return prev >= current ? prev + 1 : prev;
  }
};

auto main () -> int {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int count;
  cin >> count >> interval;
  cout << State(count).pick() + 1 << endl;
  return 0;
}

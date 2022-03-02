#include <iostream>
#include <functional>

template <typename T, typename R>
auto compose (std::function<R (T)> f) { return f; }

template <typename T, typename R, typename ...Rest>
auto compose (std::function<R (T)> f, Rest... rest) {
  return [=] (T x) {
    return compose(rest...)(f(x));
  };
}

auto main () -> int {
  std::function<int (int)> id = [] (int x) { return x; };
  auto f = compose(
    #include "compose.x.inc"
    std::function<int (int)>([] (int x) { return x * 2; }),
    std::function<int (int)>([] (int x) { return x + 1; })
  );
  std::cout << f(1) << std::endl;
  return 0;
}

#include <iostream>
#include <functional>

using std::cin, std::cout, std::endl;

template <typename ResultType, typename ArgType, typename Callable>
auto Y1 (Callable f) { return
  ([&] (auto x) -> std::function<ResultType(ArgType)> { return [&] (int t) { return f(x(x))(t); }; })
  ([&] (auto x) -> std::function<ResultType(ArgType)> { return [&] (int t) { return f(x(x))(t); }; });
}

int main () {
  auto Y = [] (auto f) { return
    ([&] (auto x) -> std::function<int (int)> { return [&] (int t) { return f(x(x))(t); }; })
    ([&] (auto x) -> std::function<int (int)> { return [&] (int t) { return f(x(x))(t); }; });
  };
  auto fib = Y1<int, int>([] (auto s) { return [&] (int n) { return n < 2 ? 1 : s(n - 1) + s(n - 2); }; });
  for (int i = 0; i < 20; ++i) cout << fib(i) << endl;

#define L(x, y) ([&] (auto x) { return y; })
  auto fib2 = L(f, L(x, L(t, f(x(x))(t)))L(x, L(t, f(x(x))(t))))L(s, L(n, n < 2 ? 1 : s(n - 1) + s(n - 2)));
  auto t = fib2(1);
#undef L

  return 0;
}

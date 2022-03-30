#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

/// An extremely simplified (and slow) version of std::function
template <typename ...>
struct Function;

template <typename R, typename ...T>
struct Function<R (T...)> {
  struct Base {
    virtual auto invoke (T ...args) -> R = 0;
    virtual ~Base () {}
  };
  template <class Functor>
  struct Derived : public Base {
    Functor f;
    Derived (const Functor &f) : f(f) {}
    auto invoke (T ...args) -> R {
      return f(args...);
    }
  };
  Base *instance;
  Function () = default;
  template <typename Functor>
  Function (const Functor &f) {
    instance = new Derived<Functor>(f);
  }
  auto operator() (T ...args) -> R {
    return instance->invoke(args...);
  }
  // make it trivially destructible at the expense of memory leaks.
  // ~Function () {
  //   delete instance;
  // }
};

using Printer = Function<void (void)>;
using Printers = std::basic_string<Printer>;

auto backtrack (std::string *str) -> int {
  int res = 0, pow = 1;
  while (str->length() > 0 && std::isdigit(str->back())) {
    res += pow * (str->back() - '0');
    pow *= 10;
    str->pop_back();
  }
  return res;
}

auto simplePrinter (std::string &&str) -> Printer {
  std::string *moved = new std::string(std::move(str));
  return [moved] () {
    for (int i = 0; i < moved->length(); ++i) putchar(moved->at(i));
  };
}

auto repeatedPrinter (const Printer &printer, int count) -> Printer {
  Printer *copy = new Printer(printer);
  return [copy, count] () {
    for (int i = 0; i < count; ++i) (*copy)();
  };
}

auto sequentialPrinter (Printers &&printers) -> Printer {
  Printers *moved = new Printers(std::move(printers));
  return [moved] () {
    for (int i = 0; i < moved->length(); ++i) moved->at(i)();
  };
}

auto scan () -> Printer {
  std::string *str = new std::string();
  Printers printers;
  char c;
  while (true) {
    c = getchar();
    if (c == EOF || c == '\n' || c == ']') break;
    if (c == '[') {
      int count = backtrack(str);
      if (!str->empty()) printers.push_back(simplePrinter(std::move(*str)));
      delete str;
      str = new std::string();
      printers.push_back(repeatedPrinter(scan(), count));
      continue;
    }
    str->push_back(c);
  }
  if (!str->empty()) printers.push_back(simplePrinter(std::move(*str)));
  delete str;
  return sequentialPrinter(std::move(printers));
}

auto main () -> int {
  Printer print = scan();
  print();
  return 0;
}

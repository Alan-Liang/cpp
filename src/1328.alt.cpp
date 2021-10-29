#include <iostream>

#define PARENS ()

#define EXPAND(...) EXPAND6(EXPAND6(EXPAND6(EXPAND6(__VA_ARGS__))))
#define EXPAND6(...) EXPAND5(EXPAND5(EXPAND5(EXPAND5(__VA_ARGS__))))
#define EXPAND5(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define debugPrint(...) \
  std::cout __VA_OPT__(EXPAND(debugPrintHelper(__VA_ARGS__))) << std::endl
#define debugPrintHelper(a1, ...) \
  << (a1) __VA_OPT__(<< ' ') \
  __VA_OPT__(debugPrintAgain PARENS (__VA_ARGS__))
#define debugPrintAgain() debugPrintHelper

int main () {
  std::string str("test message");
  debugPrint("Hello, Happy World!", 19260817, false, str);
  debugPrint("debug");
  debugPrint();
  return 0;
}

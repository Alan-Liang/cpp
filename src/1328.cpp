#include <iostream>

template <typename ...T>
void debugPrint (const T &...args);

template <>
void debugPrint () {
  std::cout << std::endl;
}

template <typename T, typename ...Rest>
void debugPrint (const T &arg, const Rest &...rest) {
  std::cout << arg << ' ';
  debugPrint(rest...);
}

int main () {
  std::string str("test message");
  debugPrint("Hello, Happy World!", 19260817, false, str);
  debugPrint("debug");
  return 0;
}

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::function<void (void)>> commands {
  {"foo", [] () { std::cout << "foo called" << std::endl; }},
  {"bar", [] () { std::cerr << "bar called" << std::endl; }},
  {"baz", [] () { std::clog << "baz called" << std::endl; }},
  {"exit", [] () { exit(0); }},
};

int main () {
  while (true) {
    std::string cmd;
    std::cin >> cmd;
    if (commands.count(cmd) == 0) {
      std::cerr << "Invalid command" << std::endl;
      continue;
    }
    commands[cmd]();
  }
  return 0;
}

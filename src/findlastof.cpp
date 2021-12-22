#include <iostream>
#include <string>

using std::cin, std::cout, std::endl;

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  std::string s;
  std::getline(cin, s);
  auto i = s.find_last_not_of(' ');
  if (i != s.npos) s = s.substr(0, i + 1);
  cout << '"' << s << '"' << endl;
  return 0;
}

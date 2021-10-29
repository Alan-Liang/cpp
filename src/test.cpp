#include <iostream>
#include <set>

using std::cin, std::cout, std::endl;

struct A {
  A () {}
  A (int id) : id(id) {}
  int id;
  bool operator< (const A &lhs) const {
    return id < lhs.id;
  }
};

int main () {
  std::string s;
  cin >> s;
  cout << (char) cin.get() << (char) cin.get();
  cin >> s;
  cout << s;
}

int main1 () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  std::set<A> s;
  std::set<int> si;
  for (const auto &x : {1,3,1,5,2,5,4,7,3,2}) {
    s.insert({x});
    si.insert(x);
  }
  for (const auto &x : s) cout << x.id << ' ';
  cout << endl;
  cout << s.upper_bound(6)->id << endl;
  si.erase(si.upper_bound(3), si.end());
  for (const auto &x : si) cout << x << ' ';
  cout << endl;
  return 0;
}

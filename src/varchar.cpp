#include <iostream>
#include <cstring>
#include <string>
#include <compare>

using std::cin, std::cout, std::endl;

template <int maxLength>
struct Varchar {
 private:
  char content[maxLength + 1];
 public:
  Varchar () { content[0] = '\0'; }
  Varchar (const std::string &s) {
    if (s.length() > maxLength) throw 999;
    strcpy(content, s.c_str());
  }
  Varchar (const char *cstr) : Varchar(std::string(cstr)) {}
  operator std::string () const { return std::string(content); }
  std::string str () const { return std::string(*this); }
  template <int A>
  Varchar operator= (const Varchar<A> &that) {
    if (that.str().length > maxLength) throw 999;
    strcpy(content, that.content);
    return *this;
  }
  template <int A>
  std::weak_ordering operator<=> (const Varchar<A> &that) const {
    return str() <=> that.str();
  }
  template <int A>
  bool operator== (const Varchar<A> &that) const { return str() == that.str(); };
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  using v = Varchar<1024>;
  v x;
  cout << x.str().length() << endl;
  x = std::string("Hello");
  v y {x};
  cout << (x == y) << endl;
  cout << (x < y) << endl;
  cout << (x > y) << endl;
  cout << x.str() << endl;
  return 0;
}

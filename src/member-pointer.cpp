#include <cstring>
#include <iostream>
#include <optional>
#include <string>

using std::cin, std::cout, std::endl;

template <typename M>
class Model {
 public:
  template <typename ValueType>
  static std::optional<M> findByKey (ValueType M::*key, const ValueType &value) {
    M result;
    result.*key = value;
    return result;
  }
  static std::optional<M> findByKey (char (M::*key)[], const char *value) {
    M result;
    strcpy(result.*key, value);
    return result;
  }
};

class M : public Model<M> {
 public:
  int id;
  std::string str;
  char cstr[100];
};

int main () {
  cout << M::findByKey(&M::id, 233)->id << endl;
  std::string str = "hello";
  cout << M::findByKey(&M::str, str)->str << endl;
  cout << M::findByKey(&M::cstr, "world")->cstr << endl;
  return 0;
}

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using std::cin, std::cout, std::endl;

enum Visibility { PUBLIC = 0, PRIVATE = 1, PROTECTED = 2, INVISIBLE = 3, NONE = 4 };

Visibility vm[4][4] = {
  {PUBLIC, INVISIBLE, PROTECTED, INVISIBLE},
  {PRIVATE, INVISIBLE, PRIVATE, INVISIBLE},
  {PROTECTED, INVISIBLE, PROTECTED, INVISIBLE},
  {INVISIBLE, INVISIBLE, INVISIBLE, INVISIBLE},
};

constexpr const char *messages[5] = {
  "Public\n",
  "Private\n",
  "Protected\n",
  "Can not Fetch\n",
  "None\n",
};

std::unordered_map<std::string, Visibility> vism {
  std::make_pair("public", PUBLIC),
  std::make_pair("private", PRIVATE),
  std::make_pair("protected", PROTECTED),
};

struct Class {
  std::unordered_map<std::string, Visibility> bases;
  std::unordered_map<std::string, Visibility> methods;
};

std::unordered_map<std::string, Class> classes;

Visibility find (const Class &c, const std::string &name) {
  if (c.methods.count(name) > 0) return c.methods.at(name);
  for (const auto &[ bn, bv ] : c.bases) {
    Visibility res = find(classes[bn], name);
    // FIXME
    if (res != NONE) return vm[bv][res];
  }
  return NONE;
}

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n;
  while (n--) {
    std::string name;
    int k0, k1;
    Class c;
    cin >> name >> k0;
    while (k0--) {
      std::string vis, name;
      cin >> vis >> name;
      c.bases[name] = vism[vis];
    }
    cin >> k1;
    while (k1--) {
      std::string vis, name;
      cin >> vis >> name;
      c.methods[name] = vism[vis];
    }
    classes[name] = c;
  }
  cin >> m;
  while (m--) {
    std::string cl, mt;
    cin >> cl >> mt;
    if (classes.count(cl) == 0) {
      cout << "None\n";
      continue;
    }
    cout << messages[find(classes[cl], mt)];
  }
  return 0;
}

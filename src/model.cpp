#include <iostream>
#include <cstring>
#include <optional>
#include <string>
#include <set>
#include <initializer_list>
#include <unordered_map>
#include <unordered_set>
#include <stddef.h>
#include <compare>

using std::cin, std::cout, std::endl;

template <int maxLength>
struct Varchar {
 private:
  template <int A>
  friend class Varchar;
  char content[maxLength + 1];
 public:
  Varchar () { content[0] = '\0'; }
  Varchar (const std::string &s) {
    if (s.length() > maxLength) throw 999;
    strcpy(content, s.c_str());
  }
  Varchar (const char *cstr) : Varchar(std::string(cstr)) {}
  template<int A>
  Varchar (const Varchar<A> &that) { *this = that; }
  operator std::string () const { return std::string(content); }
  std::string str () const { return std::string(*this); }
  template <int A>
  Varchar operator= (const Varchar<A> &that) {
    if (that.str().length() > maxLength) throw 999;
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

class College;

std::unordered_map<int, College *> collegeStore;
int nextCollegeId = 0;

template <typename M>
class Model {
 public:
  int id = -1;
  void save () {
    if (id > -1) throw "bad id";
    fstream fs { M::manager_.filename, std::ios::binary };
    fs.seekg(id * sizeof(M));
    fs.write(reinterpret_cast<char *>(this), sizeof(M));
    fs.close();
    id = nextCollegeId++;
    collegeStore[id] = new M(*static_cast<M *>(this));
  }
  void update () {
    if (id < 0) throw "bad id";
    delete collegeStore[id];
    collegeStore[id] = new M(*static_cast<M *>(this));
  }
  void remove () {
    if (id < 0) throw "bad id";
    delete collegeStore[id];
    collegeStore.erase(id);
    id = -1;
  }
  friend bool operator< (const Model &lhs, const Model &rhs) { return lhs.id < rhs.id; }

  static std::optional<M> findById (int id) {
    if (collegeStore.count(id) > 0) return *collegeStore[id];
    return std::nullopt;
  }
  // 找出第一个 key 为 value 的 Model 对象, 需要在这个 key 上有索引
  template <typename ValueType>
  static std::optional<M> findOne (ValueType M::*key, ValueType value) {
    cout << "findOne: " << M::manager_.getIndexFilename(key) << endl;
    for (const auto &[ id, college ] : collegeStore) {
      if (college->*key == value) return *college;
    }
    return std::nullopt;
  }
  template <int A>
  static std::optional<M> findOne (Varchar<A> M::*key, const std::string &value) {
    return findOne(key, Varchar<A>(value));
  }
  // 找出所有 key 为 value 的 Model 对象, 需要在这个 key 上有索引
  template <typename ValueType>
  static std::set<M> findMany (ValueType M::*key, ValueType value) {
    std::set<M> results;
    cout << "findMany: " << M::manager_.getIndexFilename(key) << endl;
    for (const auto &[ id, college ] : collegeStore) {
      if (college->*key == value) results.insert(*college);
    }
    return results;
  }
  template <int A>
  static std::set<M> findMany (Varchar<A> M::*key, std::string value) {
    return findMany(key, Varchar<A>(value));
  }
  // 找出 id 最大的 n 个 Model 对象, 需要在这个 key 上有索引
  static std::set<M> findAll (int limit) {}
 protected:
#define MODEL_OFFSETOF(x) ((size_t)(&(((M *)0)->*x)))
  struct Index {
    size_t key;
    const char *filename;
    template <typename ValueType>
    Index (ValueType M::*key, const char *filename) : key(MODEL_OFFSETOF(key)), filename(filename) {}
  };
  class Manager {
   public:
    Manager () = delete;
    const char *filename;
    std::unordered_map<size_t, const char *> indices;
    Manager (const char *filename, std::initializer_list<Index> indices_) : filename(filename) {
      for (const auto &ix : indices_) indices[ix.key] = ix.filename;
    }
    template <typename ValueType>
    const char *getIndexFilename (ValueType M::*key) {
      size_t vk = MODEL_OFFSETOF(key);
      if (indices.count(vk) == 0) throw "bad";
      return indices[vk];
    }
  };
#undef MODEL_OFFSETOF
};

class College : public Model<College> {
 public:
  Varchar<100> name;
  Varchar<11> abbrev;
  int rank;
  College () = default;
  College (std::string name, std::string abbrev, int rank) : name(name), abbrev(abbrev), rank(rank) {}
 private:
  friend class Model<College>;
  static Manager manager_;
};
College::Manager College::manager_ {
  "./data/colleges",
  {
    { &College::abbrev, "./data/college.abbrev.ix" },
    { &College::rank, "./data/college.rank.ix" },
  },
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

Varchar<10> a = "hello";
Varchar<11> b = a;
std::cout << b.str() << std::endl;


  College("Peking University", "PKU", 1).save();
  College("Tsinghua University", "THU", 1).save();
  College("Shanghai Jiao Tong University", "SJTU", 3).save();
  College("Fudan University", "FDU", 3).save();

  auto thu = College::findOne(&College::abbrev, "THU");
  thu->rank = 2;
  thu->update();

  std::cout << College::findOne(&College::abbrev, "FDU")->rank << std::endl; // 3
  std::cout << College::findOne(&College::rank, 1)->abbrev.str() << std::endl; // PKU
  for (const auto &college : College::findMany(&College::rank, 3)) {
    std::cout << college.abbrev.str() << std::endl; // SJTU FDU (in that order)
  }

  College::findOne(&College::abbrev, "FDU")->remove();
  for (const auto &college : College::findMany(&College::rank, 3)) {
    std::cout << college.abbrev.str() << std::endl; // SJTU
  }
  return 0;
}

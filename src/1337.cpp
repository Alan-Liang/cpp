#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;

template <class T, int info_len = 2>
class MemoryRiver {
 private:
  struct Metadata {
    bool hasNext : 1;
    int next : 31;
  };
  fstream file;
  string file_name;
  static constexpr size_t kSzData = std::max(sizeof(T), sizeof(int));
  static constexpr size_t kOffsetData = sizeof(int) * (info_len + 1);
  static size_t offsetof_ (int id) {
    return kOffsetData + kSzData * id;
  }
 public:
  MemoryRiver () = default;
  MemoryRiver (const string &file_name) : file_name(file_name) {}
  void initialise (string FN = "") {
    if (FN != "") file_name = FN;
    file.open(file_name, std::ios::out);
    int tmp = 0;
    for (int i = 0; i <= info_len; ++i) file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    file.close();
  }

  //读出第n个int的值赋给tmp，1_base
  void get_info (int &tmp, int n) {
    if (n > info_len) return;
    file.open(file_name, std::ios::in);
    file.seekg(n * sizeof(tmp));
    file.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
    file.close();
  }

  //将tmp写入第n个int的位置，1_base
  void write_info(int tmp, int n) {
    if (n > info_len) return;
    file.open(file_name);
    file.seekp(n * sizeof(tmp));
    file.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
    file.close();
  }

  //在文件合适位置写入类对象t，并返回写入的位置索引index
  //位置索引意味着当输入正确的位置索引index，在以下三个函数中都能顺利的找到目标对象进行操作
  //位置索引index可以取为对象写入的起始位置
  int write(T &t) {
    file.open(file_name);
    Metadata meta;
    file.seekg(0);
    file.read(reinterpret_cast<char *>(&meta), sizeof(int));
    int id = meta.next;
    if (meta.hasNext) {
      file.seekg(offsetof_(id));
      Metadata nextMeta;
      file.read(reinterpret_cast<char *>(&nextMeta), sizeof(int));
      file.seekp(0);
      file.write(reinterpret_cast<char *>(&nextMeta), sizeof(int));
    } else {
      Metadata nextMeta = meta;
      ++nextMeta.next;
      file.seekp(0);
      file.write(reinterpret_cast<char *>(&nextMeta), sizeof(int));
    }
    file.seekp(offsetof_(id));
    file.write(reinterpret_cast<char *>(&t), sizeof(t));
    file.close();
    return id;
  }

  //用t的值更新位置索引index对应的对象，保证调用的index都是由write函数产生
  void update(T &t, const int id) {
    file.open(file_name);
    file.seekp(offsetof_(id));
    file.write(reinterpret_cast<char *>(&t), sizeof(t));
    file.close();
  }

  //读出位置索引index对应的T对象的值并赋值给t，保证调用的index都是由write函数产生
  void read(T &t, const int id) {
    file.open(file_name, std::ios::in);
    file.seekg(offsetof_(id));
    file.read(reinterpret_cast<char *>(&t), sizeof(t));
    file.close();
  }

  //删除位置索引index对应的对象(不涉及空间回收时，可忽略此函数)，保证调用的index都是由write函数产生
  void Delete(int id) {
    Metadata meta;
    file.open(file_name);
    file.seekg(0);
    file.read(reinterpret_cast<char *>(&meta), sizeof(int));
    file.seekp(0);
    Metadata newMeta { .hasNext = true, .next = id };
    file.write(reinterpret_cast<char *>(&newMeta), sizeof(int));
    file.seekp(offsetof_(id));
    file.write(reinterpret_cast<char *>(&meta), sizeof(int));
    file.close();
  }
};

#endif // BPT_MEMORYRIVER_HPP

#ifndef ONLINE_JUDGE
#include <iostream>
#include <cstring>

using std::cin, std::cout, std::endl;

#define print(x) cout << x << endl

struct Payload {
  int a;
  char c[10];
  bool b;
};

int main () {
  MemoryRiver<Payload> instance;
  instance.initialise("fn");
  instance.write_info(233, 1);
  instance.write_info(666, 2);
  Payload p { .a = 19260817, .b = true };
  strcpy(p.c, "hello");
  print(instance.write(p));
  ++p.a;
  print(instance.write(p));
  p.b = false;
  print(instance.write(p));
  Payload r;
  instance.read(r, 0);
  print(r.a);
  print(r.b);
  print(r.c);
  instance.Delete(1);
  instance.Delete(2);
  print(instance.write(p));
  print(instance.write(p));
  print(instance.write(p));
  print(instance.write(p));
  print(instance.write(p));
  return 0;
}

#endif

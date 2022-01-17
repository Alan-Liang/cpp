#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <exception>

using std::cin, std::cout, std::endl;

class RequirementNotSatisfiedException : public std::exception {};

class Context {
 private:
  std::unordered_map<int, std::string> requirements_;
 public:
  Context () = default;
  void require (int id, const std::string &value) {
    if (requirements_.count(id) == 0) {
      requirements_[id] = value;
      return;
    }
    if (requirements_[id] != value) throw RequirementNotSatisfiedException();
  }
};

class Friend {
 public:
  Friend () = default;
  std::string target;
  std::vector<int> argv;

  bool satisfies (Context ctx, const std::string &name, const std::vector<std::string> &args) const {
    if (name != target) return false;
    try {
      for (int i = 0; i < args.size(); ++i) ctx.require(argv[i], args[i]);
    } catch (const RequirementNotSatisfiedException &) {
      return false;
    }
    return true;
  }
};

class Class {
 public:
  Class () = default;
  std::vector<Friend> friends;
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  std::unordered_map<std::string, Class> classes;
  int szClasses, szQueries;
  cin >> szClasses >> szQueries;
  for (int i = 0; i < szClasses; ++i) {
    Class clazz;
    std::string arg, _;
    cin >> _;
    std::unordered_map<std::string, int> argv;
    while (true) {
      cin >> arg;
      if (arg == ">") break;
      int id = argv.size() + 1;
      argv[arg] = id;
    }
    std::string nameClass;
    cin >> nameClass;

    int szFriends;
    cin >> szFriends;
    clazz.friends.reserve(szFriends);
    for (int i = 0; i < szFriends; ++i) {
      Friend friend_;
      cin >> _;
      std::unordered_map<std::string, int> argvFriend;
      std::string arg;
      while (true) {
        cin >> arg;
        if (arg == ">") break;
        int id = argvFriend.size() + 1;
        argvFriend[arg] = -id;
      }
      cin >> friend_.target >> _;
      while (true) {
        cin >> arg;
        if (arg == ">") break;
        // FIXME: hack
        int id = 0x19260817;
        if (argv.count(arg) > 0) id = argv[arg];
        if (argvFriend.count(arg) > 0) {
          if (id != 0x19260817) throw std::exception();
          id = argvFriend[arg];
        }
        if (id == 0x19260817) throw std::exception();
        friend_.argv.push_back(id);
      }

      clazz.friends.push_back(std::move(friend_));
    }

    classes[nameClass] = std::move(clazz);
  }

  for (int i = 0; i < szQueries; ++i) {
    Context ctx;

    std::string nameFriend, _, arg;
    cin >> nameFriend >> _;
    std::vector<std::string> argsFriend;
    while (true) {
      cin >> arg;
      if (arg == ">") break;
      argsFriend.push_back(arg);
    }

    std::string nameThis;
    cin >> nameThis >> _;
    int id = 1;
    while (true) {
      cin >> arg;
      if (arg == ">") break;
      ctx.require(id, arg);
      ++id;
    }

    const Class &classThis = classes[nameThis];
    bool isFriend = false;
    for (const Friend &friend_ : classThis.friends) {
      if (friend_.satisfies(ctx, nameFriend, argsFriend)) {
        isFriend = true;
        break;
      }
    }
    cout << (isFriend ? "Yes\n" : "No\n");
  }

  return 0;
}

#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl;

struct Activity {
  int timeAverage;
  int likenessLevel;
  std::string name;

  bool operator< (const Activity &that) const {
    if (timeAverage != that.timeAverage) return timeAverage > that.timeAverage;
    if (likenessLevel != that.likenessLevel) return likenessLevel < that.likenessLevel;
    return name < that.name;
  }
};

class Solution {
 private:
  std::map<std::string, std::vector<int>> map_;
  std::set<Activity> activities_;

  enum CommandType { COMMAND_TYPE_MAP, COMMAND_TYPE_SET, COMMAND_TYPE_END };
  enum Command { COMMAND_SIZE, COMMAND_INSERT, COMMAND_ERASE, COMMAND_COUNT, COMMAND_TRAVERSE, COMMAND_VISIT_VEC, COMMAND_VISIT, COMMAND_APPEND };

  CommandType getType_ () {
    std::string type;
    cin >> type;
    if (type == "map") return COMMAND_TYPE_MAP;
    if (type == "set") return COMMAND_TYPE_SET;
    if (type == "end") return COMMAND_TYPE_END;
    assert(false);
  }

  Command getCommand_ () {
    std::string command;
    cin >> command;
    if (command == "size") return COMMAND_SIZE;
    if (command == "insert") return COMMAND_INSERT;
    if (command == "erase") return COMMAND_ERASE;
    if (command == "count") return COMMAND_COUNT;
    if (command == "traverse") return COMMAND_TRAVERSE;
    if (command == "visitVec") return COMMAND_VISIT_VEC;
    if (command == "visit") return COMMAND_VISIT;
    if (command == "append") return COMMAND_APPEND;
    assert(false);
  }

  Activity getActivity_ () {
    int timeAverage, likenessLevel;
    std::string name;
    cin >> timeAverage >> likenessLevel >> name;
    return {
      .timeAverage = timeAverage,
      .likenessLevel = likenessLevel,
      .name = name,
    };
  }

  bool mapIncludes_ (const std::string &key) {
    return map_.count(key) != 0;
  }

  void error_ () {
    cout << "Error\n";
  }

 public:
  bool repl () {
    const auto type = getType_();
    switch (type) {
      case COMMAND_TYPE_MAP: {
        const auto command = getCommand_();
        switch (command) {
          case COMMAND_SIZE: {
            cout << map_.size() << endl;
            break;
          }

          case COMMAND_INSERT: {
            std::string name;
            int num;
            cin >> name >> num;
            if (mapIncludes_(name)) {
              error_();
              int _;
              for (int i = 0; i < num; ++i) cin >> _;
              break;
            }
            std::vector<int> times;
            times.reserve(num);
            for (int i = 0; i < num; ++i) {
              int time;
              cin >> time;
              times.push_back(time);
            }
            map_[name] = times;
            break;
          }

          case COMMAND_ERASE: {
            std::string name;
            cin >> name;
            if (!mapIncludes_(name)) {
              error_();
              break;
            }
            map_.erase(name);
            break;
          }

          case COMMAND_COUNT: {
            std::string name;
            cin >> name;
            cout << map_.count(name) << endl;
            break;
          }

          case COMMAND_TRAVERSE: {
            for (const auto &[ name, times ] : map_) {
              cout << name;
              for (auto time : times) cout << ' ' << time;
              cout << endl;
            }
            break;
          }

          case COMMAND_VISIT_VEC: {
            std::string name;
            int index;
            cin >> name >> index;
            if (!mapIncludes_(name)) {
              error_();
              break;
            }
            cout << map_[name].at(index) << endl;
            break;
          }

          case COMMAND_VISIT: {
            std::string name;
            cin >> name;
            if (!mapIncludes_(name)) {
              error_();
              break;
            }
            auto times = map_[name];
            cout << times.size();
            for (const int time : times) cout << ' ' << time;
            cout << endl;
            break;
          }

          case COMMAND_APPEND: {
            std::string name;
            int element;
            cin >> name >> element;
            if (!mapIncludes_(name)) {
              error_();
              break;
            }
            map_[name].push_back(element);
            break;
          }

          default:
            assert(false);
        } // switch (command)
        return true;
      } // case COMMAND_TYPE_MAP:

      case COMMAND_TYPE_SET: {
        const auto command = getCommand_();
        switch (command) {
          case COMMAND_SIZE: {
            cout << activities_.size() << endl;
            break;
          }

          case COMMAND_INSERT: {
            const auto activity = getActivity_();
            if (activities_.count(activity) != 0) {
              error_();
              break;
            }
            activities_.insert(activity);
            break;
          }

          case COMMAND_ERASE: {
            const auto activity = getActivity_();
            if (activities_.count(activity) == 0) {
              error_();
              break;
            }
            activities_.erase(activities_.find(activity));
            break;
          }

          case COMMAND_COUNT: {
            const auto activity = getActivity_();
            cout << activities_.count(activity) << endl;
            break;
          }

          case COMMAND_TRAVERSE: {
            for (const auto &activity : activities_) {
              cout << activity.timeAverage << ' ' << activity.likenessLevel << ' ' << activity.name << endl;
            }
            break;
          }

          default:
            assert(false);
        } // switch (command)
        return true;
      } // case COMMAND_TYPE_SET:

      case COMMAND_TYPE_END:
        return false;

      default:
        assert(false);
    } // switch (type)
  } // bool repl ()
}; // class Solution

int main () {
  Solution solution;
  while (solution.repl()) {}
  return 0;
}

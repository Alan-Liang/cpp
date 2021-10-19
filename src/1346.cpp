#include <cassert>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>

using std::cin, std::cout, std::endl;

/// Wrapper class for the whole solution.
class Solution {
 private:
  enum Gender { MALE, FEMALE };
  inline static const char *genderDisplayName (Gender gender) {
    if (gender == MALE) return "male";
    return "female";
  }
  struct Student {
   private:
    mutable bool dirty_ = true;
    mutable int averageScore_;

   public:
    std::string name;
    Gender gender;
    int classNumber;
    mutable int scores[9];
    mutable int scoreChanges[9];
    mutable int rank;

    Student () {
      for (int i = 0; i < 9; ++i) scoreChanges[i] = -1;
    }
    Student (std::string name) : name(name) {
      for (int i = 0; i < 9; ++i) scoreChanges[i] = -1;
    }

    inline bool operator< (const Student &that) const {
      return name < that.name;
    }

    inline void markDirty () const { dirty_ = true; }
    inline bool isDirty () const { return dirty_; }
    inline int getAverageScore () const {
      if (Solution::solution.ignoreDirty_) {
        int avg = 0;
        for (int i = 0; i < 9; ++i) avg += scores[i];
        return avg / 9;
      }
      if (dirty_) {
        dirty_ = false;
        averageScore_ = 0;
        for (int i = 0; i < 9; ++i) {
          if (scoreChanges[i] >= 0) averageScore_ += scoreChanges[i];
          else averageScore_ += scores[i];
        }
        averageScore_ /= 9;
      }
      return averageScore_;
    }
    inline void applyChanges () const {
      for (int i = 0; i < 9; ++i) {
        // set to -1 to reset, because score is in [0, 100]
        if (scoreChanges[i] >= 0) {
          scores[i] = scoreChanges[i];
          scoreChanges[i] = -1;
        }
      }
      dirty_ = true;
    }

    /// functor to compare students' scores.
    class scoreLessThan {
     public:
      inline bool operator() (const std::string &lhsName, const std::string &rhsName) const {
        // FIXME: hack
        // this hack was added to access value of `solution` from the functor.
        const Student &lhs = Solution::solution.studentInfo_[lhsName];
        const Student &rhs = Solution::solution.studentInfo_[rhsName];
        if (lhs.getAverageScore() != rhs.getAverageScore()) return lhs.getAverageScore() > rhs.getAverageScore();
        for (int i = 0; i < 9; i++) if (lhs.scores[i] != rhs.scores[i]) return lhs.scores[i] > rhs.scores[i];
        return lhsName < rhsName;
      }
    };
  };
  /// Base class for all commands.
  class BaseCommand {
   public:
    // static methods cannot be virtual.
    static void execute (Solution &solution) {
      assert(false);
    };
  };

  /// whether we have started the scoreboard.
  bool started_ = false;
  /**
   * FIXME: hack
   * whether `Student` should ignore the dirty flag.
   * This is kind of magic :-)
   *
   * if set to true, then `Student` would use old data to calculate average score,
   * causing `Student::scoreLessThan` to behave like if no data was changed,
   * therefore ensuring consistent behaviour of `std::set::erase(std::string)`.
   */
  bool ignoreDirty_ = false;
  /// The set of students names, ordered by score.
  std::set<std::string, Student::scoreLessThan> scoreboard_;
  /// Index of student name.
  std::unordered_map<std::string, Student> studentInfo_;
  /// The set of student names that need an update during the next flush.
  std::unordered_set<std::string> namesUpdateNeeded_;

  void updateRankings_ () {
    int i = 0;
    for (const std::string &name : scoreboard_) {
      ++i; // 1-based rankings
      studentInfo_[name].rank = i;
    }
  }

  class Add : public virtual BaseCommand {
   private:
    static constexpr char errorStarted[] = "[Error]Cannot add student now.\n";
    static constexpr char errorDuplicate[] = "[Error]Add failed.\n";

   public:
    inline static void execute (Solution &solution) {
      Student student;
      char gender;
      cin >> student.name >> gender >> student.classNumber;
      student.gender = gender == 'M' ? MALE : FEMALE;
      for (int i = 0; i < 9; ++i) cin >> student.scores[i];

      if (solution.started_) {
        cout << errorStarted;
        return;
      }
      if (solution.studentInfo_.count(student.name) > 0) {
        cout << errorDuplicate;
        return;
      }

      solution.studentInfo_[student.name] = student;
    }
  };

  class Start : public virtual BaseCommand {
   public:
    static void execute (Solution &solution) {
      solution.started_ = true;
      for (const auto &[ _, student ] : solution.studentInfo_) solution.scoreboard_.insert(student.name);
      solution.updateRankings_();
    }
  };

  class Update : public virtual BaseCommand {
   private:
    static constexpr char errorNotFound[] = "[Error]Update failed.\n";

   public:
    inline static void execute (Solution &solution) {
      std::string name;
      int code, score;
      cin >> name >> code >> score;

      if (solution.studentInfo_.count(name) == 0) {
        cout << errorNotFound;
        return;
      }

      const Student &student = solution.studentInfo_[name];
      student.scoreChanges[code] = score;
      student.markDirty();
      solution.namesUpdateNeeded_.insert(name);
    }
  };

  class Flush : public virtual BaseCommand {
   public:
    static void execute (Solution &solution) {
      solution.ignoreDirty_ = true;
      for (const auto &name : solution.namesUpdateNeeded_) solution.scoreboard_.erase(name);
      solution.ignoreDirty_ = false;
      for (const auto &name : solution.namesUpdateNeeded_) {
        solution.studentInfo_[name].applyChanges();
        solution.scoreboard_.insert(name);
      }
      solution.namesUpdateNeeded_.clear();

      solution.updateRankings_();
    }
  };

  class PrintList : public virtual BaseCommand {
   public:
    static void execute (Solution &solution) {
      for (const std::string &name : solution.scoreboard_) {
        const Student &student = solution.studentInfo_[name];
        cout << student.rank << ' '
             << student.name << ' '
             << genderDisplayName(student.gender) << ' '
             << student.classNumber << ' '
             << student.getAverageScore() << '\n';
      }
    }
  };

  class Query : public virtual BaseCommand {
   private:
    static constexpr char errorNotFound[] = "[Error]Query failed.\n";

   public:
    inline static void execute (Solution &solution) {
      std::string name;
      cin >> name;
      if (solution.studentInfo_.count(name) == 0) {
        cout << errorNotFound;
        return;
      }
      cout << "STUDENT " << name << " NOW AT RANKING " << solution.studentInfo_[name].rank << '\n';
    }
  };

 public:
  static Solution solution;
  void repl () {
    started_ = false;
    while (true) {
      std::string inputCommand;
      cin >> inputCommand;
      // hack here to optimize for speed.
      switch (inputCommand[0]) {
        case 'A': { Add::execute(*this); break; }
        case 'S': { Start::execute(*this); break; }
        case 'U': { Update::execute(*this); break; }
        case 'F': { Flush::execute(*this); break; }
        case 'P': { PrintList::execute(*this); break; }
        case 'Q': { Query::execute(*this); break; }
        case 'E': return;
        default: {
#ifndef ONLINE_JUDGE
          cout << inputCommand << endl;
#endif
          assert(false);
        }
      }
    }
  }
};

Solution Solution::solution;

int main () {
#ifdef ONLINE_JUDGE
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
#endif

#ifdef DEBUG_VSCODE
  freopen("1346.in", "r", stdin);
#endif

  Solution::solution.repl();

  return 0;
}

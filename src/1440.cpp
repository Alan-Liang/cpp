#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
// is it permitted?
#include <string>
#include <sstream>
class BaseJudger {
public:
    BaseJudger (size_t time_limit , size_t memory_limit ,
                const char *answer) : answer_(answer), time_limit_(time_limit), memory_limit_(memory_limit), score_(0) {}

    virtual void Submit (size_t time , size_t memory , const char *output) = 0;

    size_t GetScore () const { return score_; }

    virtual ~BaseJudger () {}

protected:
    const char *answer_;
    const size_t time_limit_;
    const size_t memory_limit_;
    size_t score_;

    virtual bool CheckAnswer (const char *output) const {
        // the output must equal to the answer
        return strcmp(answer_ , output) == 0;
    }
};


class ICPCJudger : public BaseJudger {
 public:
  void Submit (size_t time, size_t memory, const char *output) {
    if (time > time_limit_) return;
    if (memory > memory_limit_) return;
    if (!strcmp(output, answer_)) return;
    score_ = 100;
  }
};

class OIJudger : public BaseJudger {
 private:
  bool submitted_ = false;
 public:
  void Submit (size_t time, size_t memory, const char *output) {
    if (submitted_) {
      score_ = 0;
      return;
    }
    submitted_ = true;
    if (time > time_limit_) return;
    if (memory > memory_limit_) return;
    std::istringstream out {output};
    std::istringstream ans {answer_};
    while (!out.eof() && !ans.eof()) {
      std::string l1, l2;
      std::getline(out, l1);
      std::getline(out, l2);
      auto i1 = l1.find_last_of(' ');
      auto i2 = l2.find_last_of(' ');
      if (i1 !== std::npos) {}
      l1 = l1.substr(0, i1);
    }
    score_ = 100;
  }
};

class SpacialJudger : public BaseJudger {};
// todo

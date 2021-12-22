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
                const char *answer) : time_limit_(time_limit), memory_limit_(memory_limit), score_(0) {
                  answer_ = new char[strlen(answer) + 1];
                  strcpy(answer_, answer);
                }

    virtual void Submit (size_t time , size_t memory , const char *output) = 0;

    size_t GetScore () const { return score_; }

    virtual ~BaseJudger () { delete[] answer_; }

protected:
    char *answer_;
    const size_t time_limit_;
    const size_t memory_limit_;
    size_t score_;

    virtual bool CheckAnswer (const char *output) const {
        // the output must equal to the answer
        throw 1;
        return strcmp(answer_ , output) == 0;
    }
};


class ICPCJudger : public BaseJudger {
 public:
  ICPCJudger (size_t time_limit, size_t memory_limit, const char *answer) : BaseJudger(time_limit, memory_limit, answer) {}
  void Submit (size_t time, size_t memory, const char *output) {
    if (time > BaseJudger::time_limit_) return;
    if (memory > BaseJudger::memory_limit_) return;
    if (strcmp(output, BaseJudger::answer_) != 0) return;
    BaseJudger::score_ = 100;
  }
};

class OIJudger : public BaseJudger {
 private:
  bool submitted_ = false;
 public:
  OIJudger (size_t time_limit, size_t memory_limit, const char *answer) : BaseJudger(time_limit, memory_limit, answer) {}
  void Submit (size_t time, size_t memory, const char *output) {
    if (submitted_) {
      BaseJudger::score_ = 0;
      return;
    }
    submitted_ = true;
    if (time > BaseJudger::time_limit_) return;
    if (memory > BaseJudger::memory_limit_) return;
    std::istringstream out {output};
    std::istringstream ans {BaseJudger::answer_};
    while (!out.eof() || !ans.eof()) {
      std::string l1, l2;
      std::getline(out, l1);
      std::getline(ans, l2);
      while (l1.length() > 0 && l1.back() == ' ') l1.pop_back();
      while (l2.length() > 0 && l2.back() == ' ') l2.pop_back();
      if (l1 != l2) {
        BaseJudger::score_ = 0;
        return;
      }
    }
    BaseJudger::score_ = 100;
  }
};

class SpacialJudger : public BaseJudger {
 private:
  const size_t full_score_time_, full_score_memory_;
 public:
  SpacialJudger (size_t time_limit, size_t memory_limit, size_t full_score_time, size_t full_score_memory, const char *answer) : BaseJudger(time_limit, memory_limit, answer), full_score_time_(full_score_time), full_score_memory_(full_score_memory) {}

  void Submit (size_t time, size_t memory, const char *output) {
    if (time > BaseJudger::time_limit_) return;
    if (memory > BaseJudger::memory_limit_) return;
    if (strcmp(output, BaseJudger::answer_) != 0) return;
    size_t timeScore, memoryScore;
    if (time <= full_score_time_) timeScore = 100;
    else timeScore = ((double) (BaseJudger::time_limit_ - time)) / ((double) BaseJudger::time_limit_ - full_score_time_) * 100.0;
    if (memory <= full_score_memory_) memoryScore = 100;
    else memoryScore = ((double) (BaseJudger::memory_limit_ - memory)) / ((double) BaseJudger::memory_limit_ - full_score_memory_) * 100.0;
    size_t score = (timeScore * memoryScore) / 100;
    if (score > BaseJudger::score_) BaseJudger::score_ = score;
  }
};

#ifndef ONLINE_JUDGE
#include <iostream>
using namespace std;


string get_data () {
    // ignore empty lines
    string ret = "" , line;
    while (getline(cin , line)) {
        if (line.length() == 0) {
            continue;
        }
        if (line == "#####") {
            break;
        }
        ret += line + "\n";
    }
    return std::move(ret);
}

int main () {
    char judger_name[100];
    cin >> judger_name;
    size_t time_limit , mem_limit;
    cin >> time_limit >> mem_limit;
    BaseJudger *judger = nullptr;
    string tmp;
    if (strcmp(judger_name , "OIJudger") == 0) {
        tmp = get_data();
        judger = new OIJudger(time_limit , mem_limit , tmp.c_str());
    } else if (strcmp(judger_name , "ICPCJudger") == 0) {
        tmp = get_data();
        judger = new ICPCJudger(time_limit , mem_limit , tmp.c_str());
    } else if (strcmp(judger_name ,"SpacialJudger") == 0) {
        size_t full_score_time , full_score_memory;
        cin >> full_score_time >> full_score_memory;
        tmp = get_data();
        judger = new SpacialJudger(time_limit , mem_limit , full_score_time ,
                                   full_score_memory , tmp.c_str());
    } else {
        cout << "Unknown Judger type" << endl;
        return 0;
    }

    size_t submit_time , submit_mem;
    while (cin >> submit_time >> submit_mem) {
        tmp = get_data();
        const char *output = tmp.c_str();
        judger->Submit(submit_time , submit_mem , output);
    }
    cout << judger->GetScore() << endl;
    delete judger;
    return 0;
}
#endif

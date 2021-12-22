#include <iostream>
#include <string>

using std::cin, std::cout, std::endl;

#include <cstdlib>
#include <algorithm>

#ifdef DEBUG
#include "1292.data.inc"
#else
/*
const kYears = 2
const kMonthsInYear = 12

const presum = (prev, curr) => [ ...prev, prev[prev.length - 1] + curr ]
const isLeap = year => year % 100 === 0 ? year % 400 === 0 : year % 4 === 0
const daysInYear = Array.from(Array(kYears - 1).keys()).map(isLeap).map(leap => leap ? 366 : 365)
const yearOffset = daysInYear

const kDaysInMonth = [ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ]
const kDaysInMonthLeap = kDaysInMonth.map((d, m) => m == 1 ? d + 1 : d)

console.log(`
constexpr int kYears = ${kYears};
constexpr int kMonthsInYear = ${kMonthsInYear};
constexpr int kDaysInMonth[kMonthsInYear] = {${kDaysInMonth.join(',')}};
constexpr int kDaysInMonthLeap[kMonthsInYear] = {${kDaysInMonthLeap.join(',')}};
constexpr int kMonthOffset[kMonthsInYear] = {${kDaysInMonth.slice(0, -1).reduce(presum, [ 0 ]).join(',')}};
constexpr int kMonthOffsetLeap[kMonthsInYear] = {${kDaysInMonthLeap.slice(0, -1).reduce(presum, [ 0 ]).join(',')}};
constexpr int kYearOffset[kYears] = {${daysInYear.reduce(presum, [ 0 ]).join(',')}};
`.trim())
*/
// TODO
constexpr int kYears = 2;
constexpr int kMonthsInYear = 12;
constexpr int kDaysInMonth[kMonthsInYear] = {31,28,31,30,31,30,31,31,30,31,30,31};
constexpr int kDaysInMonthLeap[kMonthsInYear] = {31,29,31,30,31,30,31,31,30,31,30,31};
constexpr int kMonthOffset[kMonthsInYear] = {0,31,59,90,120,151,181,212,243,273,304,334};
constexpr int kMonthOffsetLeap[kMonthsInYear] = {0,31,60,91,121,152,182,213,244,274,305,335};
constexpr int kYearOffset[kYears] = {0,365};
#endif

class Calendar {
 private:
  static bool isLeap_ (int year) { return year % 100 == 0 ? year % 400 == 0 : year % 4 == 0; }
  /// Finds the index of the last element in a sorted array that is no more than upperBound.
  static int find_ (const int *array, int length, int avgInterval, int upperBound) {
    int pos = std::min(upperBound / avgInterval, length - 1);
    while (array[pos] > upperBound) {
      if (pos == 0) return pos;
      --pos;
    }
    if (pos == 0) return pos;
    while (array[pos] <= upperBound) {
      if (pos == length - 1) return pos;
      ++pos;
    }
    return pos - 1;
  }
  static std::tuple<int, int, int> ymdFromEpoch_ (int epochTime) {
    int y = find_(kYearOffset, kYears, 365, epochTime);
    const auto &monthOffset = isLeap_(y + 1) ? kMonthOffsetLeap : kMonthOffset;
    int m = find_(monthOffset, kMonthsInYear, 30, epochTime - kYearOffset[y]);
    int d = epochTime - kYearOffset[y] - monthOffset[m];
    return { y + 1, m + 1, d + 1 };
  }
  static int epochFromYmd_ (int y, int m, int d) {
    return kYearOffset[y - 1] + (isLeap_(y) ? kMonthOffsetLeap : kMonthOffset)[m - 1] + d - 1;
  }

  int epochTime_ = 0;
  Calendar (int epochTime) : epochTime_(epochTime) {}
  void readString_ (const std::string str) {
    epochTime_ = epochFromYmd_(
      std::stoi(str.substr(0, 4)),
      std::stoi(str.substr(5, 2)),
      std::stoi(str.substr(8, 2))
    );
  }
 public:
  Calendar () {}
  Calendar (int y, int m, int d) : epochTime_(epochFromYmd_(y, m, d)) {}
  Calendar (const std::string &str) { readString_(str); }
  bool operator== (const Calendar &that) const { return epochTime_ == that.epochTime_; }
  bool operator!= (const Calendar &that) const { return epochTime_ != that.epochTime_; }
  bool operator<  (const Calendar &that) const { return epochTime_ <  that.epochTime_; }
  bool operator>  (const Calendar &that) const { return epochTime_ >  that.epochTime_; }
  bool operator<= (const Calendar &that) const { return epochTime_ <= that.epochTime_; }
  bool operator>= (const Calendar &that) const { return epochTime_ >= that.epochTime_; }
  Calendar &operator++ () { ++epochTime_; return *this; }
  Calendar operator++ (int) { ++epochTime_; return Calendar(epochTime_ - 1); }
  Calendar &operator-- () { --epochTime_; return *this; }
  Calendar operator-- (int) { --epochTime_; return Calendar(epochTime_ + 1); }
  Calendar &operator+= (int delta) { epochTime_ += delta; return *this; }
  Calendar &operator-= (int delta) { epochTime_ -= delta; return *this; }
  Calendar operator+ (int delta) const { return Calendar(epochTime_ + delta); }
  Calendar operator- (int delta) const { return Calendar(epochTime_ - delta); }
  int operator- (const Calendar &that) const { return epochTime_ - that.epochTime_; }
  operator std::string () const {
    auto [ y, m, d ] = ymdFromEpoch_(epochTime_);
    char res[11];
    std::sprintf(res, "%04d-%02d-%02d", y, m, d);
    return res;
  }
  friend std::istream &operator>> (std::istream &is, Calendar &cal) {
    std::string str;
    is >> str;
    cal.readString_(str);
    return is;
  }
  friend std::ostream &operator<< (std::ostream &os, const Calendar &cal) { os << static_cast<std::string>(cal); return os; }
  int getday () const { return (epochTime_ % 7 + 1) % 7; }
};

const Calendar operator ""_C (const char *col, size_t n) { return Calendar(col); }

using std::string;

void (*tests[]) () = {
  [] {
    Calendar c;
  },
  [] {
    Calendar c(1,1,1);
    cin >> c;
    cout << (c+=0)+0 << endl;
    cout << c.getday() << endl;
    cin >> c;
    cout << c << endl;
    cout << c.getday() << endl;
  },
  [] {
    Calendar c;
    c = Calendar("2010-01-01");
    cout << c.getday() << endl;
    cout << c << endl;
    cout << c.getday() << endl;
    cout << ++c << endl;
    cout << c.getday() << endl;
    cout << (c += 1) << endl;
    cout << c.getday() << endl;
    cout << (c -= 1) << endl;
    cout << c.getday() << endl;
    cout << --c << endl;
    cout << (c+=1)-(c-=1) << endl;
    cout << c-c << endl;
    cout << (c-=1) - (c+=1) << endl;
  },
  [] {
    Calendar cend = Calendar("1005-12-31");
    Calendar c(1000,1,1);
    Calendar startc;
    startc = c;
    for (; c < cend; c+=2) {
        cout << string(c++) << endl;
        cout << (++c).getday() << endl;
    }
    for (; c >= startc; c-=10) {
        cout << string(c--) << endl;
        cout << (--c).getday() << endl;
    }
    c = Calendar("0001-01-01")+1400;
    Calendar cc = c - 1400;
    cout << c << cc << endl;
    for (; cc < c + 1400; ++cc) {
        cout << (cc > c) << (cc == c) << (cc < c) << (cc == c) << (cc != c);
        cout << (cc-c);
    }
  },
  [] {
    Calendar c(400,2,29);
    c+=((c+2650000)-c);
    c-=((c+2650000)-c);
    c++;
    c-=(c-(c+1));
    --c;
    c+=(c-(c+1));
    cout << c+(c-c) << endl;
    cout << c.getday() << endl;
    cout << "2009-01-01"_C - 365;
  },
};

int main () {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  for (int i = 3; i < 5; ++i) tests[i]();
  return 0;
}

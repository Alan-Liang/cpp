#include <algorithm>
#include <cstring>
#include <vector>

enum Kind { kEmpty, kChar, kC, kCopy, kJoin, kSlice };
struct EmptyData {};
struct CharData { char ch; };
struct CData { const char* c; };
struct CopyData { const str* src; };
struct JoinData { str* sep; const std::vector<str> *strs; };
struct SliceData { int left; int right; const str* beforeSlice; };
union Data { struct EmptyData emptyData; struct CharData charData; struct CData cData; struct CopyData copyData; struct JoinData joinData; struct SliceData sliceData; ~Data () {}; };

class str {
private:
  Kind kind;
  Data data = {};
public:
  str () : kind(kEmpty) {}
  str (const char &c) : kind(kChar) { data.charData.ch = c; }
  str (const char *&& s_) : kind(kC) { data.cData.c = s_; }
  str &operator= (const char *&& s_) {
    kind = kC;
    data.cData.c = s_;
  }

  str (const str &other) : kind(kCopy) { data.copyData.src = &other; }

  str &operator= (const str &other) {
    kind = kCopy;
    data.copyData.src = &other;
  }

  const char &operator[] (size_t pos) {
    switch (kind) {
    case kChar: return data.charData.ch;
    case kC: return data.cData.c[pos];
    case kCopy: return ((str) *(data.copyData.src))[pos];
    case kJoin:
      size_t current;
      const size_t lengthSep = data.joinData.sep->len();
      for (str s : *(data.joinData.strs)) {
        size_t length = s.len();
        current += length;
        if (current > pos) return s[pos - (current - length)];
        current += lengthSep;
        if (current > pos) return ((str) *(data.joinData.sep))[pos - (current - lengthSep)];
      }
    case kSlice: return ((str) *(data.sliceData.beforeSlice))[pos + data.sliceData.left];
    }
  }

  size_t len () {
    switch (kind) {
    case kEmpty: return 0;
    case kChar: return 1;
    case kC: return strlen(data.cData.c);
    case kCopy: return ((str) *data.copyData.src).len();
    case kJoin:
      if (data.joinData.strs->size() == 0) return 0;
      size_t length = (data.joinData.strs->size() - 1) * data.joinData.sep->len();
      for (str s : *(data.joinData.strs)) length += s.len();
      return length;
    case kSlice: return data.sliceData.right - data.sliceData.left;
    }
  }

  str join (const std::vector<str> &strs) {
    str* result = new str;
    result->kind = kJoin;
    result->data.joinData.sep = this;
    result->data.joinData.strs = &strs;
    return *result;
  }

  str slice (size_t l, size_t r) {
    str* result = new str;
    result->kind = kSlice;
    result->data.sliceData.left = l;
    result->data.sliceData.right = r;
    result->data.sliceData.beforeSlice = this;
    return *result;
  }

  ~str () {}
};

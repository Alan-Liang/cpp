#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

namespace panic {

using ArrayId = int;
class {
 private:
  int next_ = 0;
 public:
  int next () { return next_++; }
} arrayId;

enum ArrayType { ARRAY, INT };
struct ArrayPayload {
  using ContentType = std::shared_ptr<std::vector<std::shared_ptr<ArrayPayload>>>;
  ArrayId id;
  ArrayType type;
  int value;
  ContentType content;
  ArrayPayload (ArrayId id) : id(id), content(new std::vector<std::shared_ptr<ArrayPayload>>), type(ARRAY) {}
  ArrayPayload (ArrayId id, int value) : id(id), value(value), type(INT) {}
};

class Array {
 private:
  using PtrType = std::shared_ptr<ArrayPayload>;
  ArrayId id_;
  PtrType payload_;
  PtrType copyIfNeeded_ (const PtrType &that) {
    if (that->type == INT) return PtrType(new ArrayPayload(-1, that->value));
    return that;
  }
  explicit Array (const PtrType &payload) : id_(payload->id), payload_(copyIfNeeded_(payload)) {}
 public:
  Array () : id_(arrayId.next()), payload_(new ArrayPayload(id_)) {}
  explicit Array (int value): id_(-1), payload_(new ArrayPayload(id_, value)) {}
  void append (const Array &other) {
    const int size = other.payload_->content->size();
    for (int i = 0; i < size; ++i) payload_->content->push_back(copyIfNeeded_(other.payload_->content->at(i)));
  }
  Array pop () {
    Array result { payload_->content->back() };
    payload_->content->pop_back();
    return result;
  }
  Array &operator[] (size_t i) {
    return Array(payload_->content->at(i));
  }
  friend std::ostream &operator<< (std::ostream &os, const Array &ls) {
    return os;
  }
};

} // namespace panic

using pylist = panic::Array;

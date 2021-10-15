#include <cstdlib>

class MemoryPoolManager {
private:
  char *head;
  size_t block_size, block_cnt;
public:
  MemoryPoolManager (char *ptr, size_t block_size_, size_t block_cnt_) : head(ptr), block_size(block_size_), block_cnt(block_cnt_) {
    for (size_t i = 0; i < block_cnt; i++) {
      *((size_t *) (head + block_size * i)) = (size_t) head + block_size * (i + 1);
    }
  }

  void *allocate () {
    if (block_cnt == 0) return nullptr;
    block_cnt--;
    void *ptr = (void *) head;
    head = (char *) *((size_t *) head);
    return ptr;
  }

  void free (void *ptr) {
    block_cnt++;
    *((size_t *) ptr) = (size_t) head;
    head = (char *) ptr;
  }
};

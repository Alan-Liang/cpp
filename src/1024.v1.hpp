// explicit free list
#include <cstdlib>

class MemoryPoolManager {
private:
  char *head;
  size_t block_size, block_cnt;
public:
  MemoryPoolManager (char *ptr, size_t block_size_, size_t block_cnt_) : head(ptr), block_size(block_size_), block_cnt(block_cnt_) {
    size_t listBlocks = (block_cnt / (block_size * 8)) + (block_cnt % (block_size * 8) ? 1 : 0);
    char* realHead = head + block_size * listBlocks;
    char* current = head;
    for (size_t i = 0; i < listBlocks * block_size; i++) *(current++) = 0;
  }

  void *allocate () {
    size_t listBlocks = (block_cnt / (block_size * 8)) + (block_cnt % (block_size * 8) ? 1 : 0);
    char* realHead = head + block_size * listBlocks;
    for (size_t blockId = 0; blockId < block_cnt - listBlocks; blockId++) {
      if (*(head + blockId / 8) == -1) {
        blockId += 8;
        continue;
      }
      char mask = 1 << (blockId % 8);
      if (!(*(head + blockId / 8) & mask)) {
        *(head + blockId / 8) |= mask;
        return (void *) (realHead + blockId * block_size);
      }
    }
    return nullptr;
  }

  void free (void *ptr) {
    if (ptr == nullptr) return;
    size_t listBlocks = (block_cnt / (block_size * 8)) + (block_cnt % (block_size * 8) ? 1 : 0);
    char* realHead = head + block_size * listBlocks;
    size_t blockId = ((char *) ptr - realHead) / block_size;
    if (!(*(head + blockId / 8) & (1 << (blockId % 8)))) return;
    *(head + blockId / 8) ^= (1 << (blockId % 8));
  }
};

//
// Created by mactavish on 15-4-16.
//

#ifndef MEMPOOL_MEMPOOL_H
#define MEMPOOL_MEMPOOL_H


namespace verihy{

struct mem_chunk{
    mem_chunk *prev;
    mem_chunk *next;
    uint32_t size;
};

class mem_list{
  public:
    static const int extra_size = 3 * sizeof(void *);
    mem_list *next;
    mem_chunk *available;
    mem_chunk *used;

    void free_chunklist(mem_chunk *chunk);

    uint32_t size;

    explicit mem_list(const uint32_t sz):
            next(nullptr), available(nullptr),
            used(nullptr), size(sz){}
    ~mem_list();

    void* get();
    void put(mem_chunk *chunk);

};


class mem_pool{
  private:
    mem_list *mlist;
  public:
    mem_pool():mlist(nullptr){}
    ~mem_pool();
    mem_pool(const mem_pool &rhs) = delete;
    mem_pool(mem_pool &&rhs) = delete;

    void* alloc(uint32_t size);
    void dealloc(void *addr);

};

} // namespace verihy

#endif //MEMPOOL_MEMPOOL_H

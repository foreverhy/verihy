#ifndef VERIHY_MEMPOOL_H
#define VERIHY_MEMPOOL_H 
#include <cstdint>
#include <iostream>
#include <mutex>

namespace verihy{


struct mem_block{
    mem_block *prev;
    mem_block *next;
    uint32_t size;
    uint32_t magic;
    int end[0];
};

class mem_pool{
  public:
    mem_block *head_;
    std::size_t totalsz;
    std::mutex mtx;
    static const std::size_t EXTRASPACE = sizeof(struct mem_block);
    static const std::size_t MAXSIZE = 1024 * 1024 * 20;
  public:
    mem_pool():head_(nullptr), totalsz(0){}
    ~mem_pool();

    void* alloc(std::size_t sz);
    int dealloc(void *addr);

};


} // namespace


#endif

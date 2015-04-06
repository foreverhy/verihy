#include "mempool.h"
#include <cstdlib>


//TODO CAS lock free

namespace verihy{

mem_pool::~mem_pool(){
    for (auto p = head_; p;){
        auto tmp = p;
        p = p->next;
        free(tmp);
    }
}

void* mem_pool::alloc(size_t sz){
    mtx.lock();
    if (totalsz + sz > MAXSIZE){
        mtx.unlock();
        return nullptr;
    }
    totalsz += sz;
    for(auto p = head_ ; p; p = p->next){
        if (p->size >= sz){
            if (p->next){
                p->next->prev = p->prev;
            }
            if (p->prev){
                p->prev->next = p->next;
            }else{
                head_ = p->next;
            }
            p->next = p->prev = nullptr;
            mtx.unlock();
            return p + sizeof(struct mem_block);
        }
    }
    void *addr = malloc(sz + EXTRASPACE);
    auto mb = static_cast<mem_block*>(addr);
    mb->size = sz;
    mtx.unlock();
    return mb->end;
}

int mem_pool::dealloc(void *addr){
    auto block = reinterpret_cast<mem_block*>(static_cast<char*>(addr) - sizeof(struct mem_block));
    block->prev = nullptr;
    mtx.lock();
    block->next = head_; 
    if (head_){
        head_->prev = block;
    }
    head_ = block;
    mtx.unlock();
    return 0;
}

} // namespace verihy

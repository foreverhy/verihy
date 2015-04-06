#include "../../memory/mempool.h"


int main(){
    using verihy::mem_pool;
    mem_pool mp;
    int *t = static_cast<int*>(mp.alloc(sizeof(int)));
    *t = 3;
    mp.dealloc(t);
    return 0;
}

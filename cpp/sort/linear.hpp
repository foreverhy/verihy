#ifndef VERIHY_SORT_LINEAR_HPP
#define VERIHY_SORT_LINEAR_HPP


#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iterator>

namespace verihy{

namespace sort{

    
template<typename RandomIt>
void radix_sort(RandomIt first, RandomIt last){
    if(first + 1 == last){
        return ;
    }
    const int digits = 16;
    const int offset = 4;
    int shift = 0;
    int count[digits];
    std::vector<typename std::iterator_traits<RandomIt>::value_type> tmp(last - first, 0);
    while(true){
        std::memset(count, 0, sizeof count);
        bool done = true;
        for(auto px = first; px != last; ++px){
            auto trx = ((*px) >> shift) & 0xf;
            if(trx){
                done = false;
            }
            count[trx]++;
        }
        if(done){
            break;
        }
        for(int i = 0; i < digits; ++i){
            count[i] += count[i - 1];
        }
        for(auto px = first; px != last; ++px){
            auto trx = ((*px) >> shift) & 0xf;
            tmp[count[trx] - 1] = *px;
            count[trx]--;
        }
        shift += offset;
        int st = 0;
        std::for_each(first, last, [&st,&tmp](decltype(*first) x){ x = tmp[st++]; });
    }
}



}// namespace sort

}// namespace verihy


#endif

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H 1

#include<algorithm>
#include<exception>
#include<iostream>

namespace verihy {

namespace data_structure{

namespace priority_queue {

template<typename T>
class priority_queue {
 private:
    T *heap;
    unsigned len;
    unsigned last;
    void swim(unsigned k){
        while(k > 1 && heap[k] < heap[k>>1]){
            std::swap(heap[k], heap[k>>1]);
            k >>= 1;
        }
    }
    void sink(unsigned k){
        while((k << 1) <= last){
            unsigned j = k<<1;
            if(((j|1) <= last && heap[j] > heap[j|1])){
                ++j;
            }
            if(heap[k] < heap[j])break;
            std::swap(heap[k], heap[j]);
            k = j;
        }
    }
 public:
    priority_queue(unsigned len){
            heap = new T[len+1];
            this->len = len;
            last = 0;
        }
        ~priority_queue(){
            delete []heap;
        }
        unsigned size(){
            return last;
        }
        bool is_empty(){
            return 0 == last;
        }
        bool insert(T x){
            if(last >= len){
                throw last;
            }
            heap[++last] = x;
            swim(last);
            return true;
        }
        T top(){
            if(0 == last){
                throw last;
            }
            return heap[1];
        }
        T pop(){
            if(0 == last){
                throw last;
            }
            T tmp = heap[1];
            heap[1] = heap[last--];
            sink(1);
            return tmp;
        }

};


}// namespace priority_queue

}// namespace data_structure 

}// namespace verihy

#endif //PRIORITY_QUEUE_H

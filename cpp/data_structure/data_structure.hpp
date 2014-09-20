#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H 1

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



namespace binary_search_tree {



template<typename Tkey, typename Tval>
class node{
  public:
    Tkey key;
    Tval val;
    node *left, *right;
    unsigned size;

    node(Tkey key, Tval val){
        this->key = key;
        this->val = val;
        left = right = NULL;
        size = 0;
    }

    ~node(){
    }
};

class KeyNotFoundError:std::exception {
  public:
    KeyNotFoundError(){
        std::cout<<"Error! Key not found!"<<std::endl;
    }
};


template<typename Tkey, typename Tval>
class binary_search_tree {
  private:
    node<Tkey, Tval> *root;

    void delete_tree(node<Tkey, Tval>* &h) {
        if(NULL == h){
            return;
        }
        delete_tree(h->left);
        delete_tree(h->right);
        delete h;
    }


    Tval get(Tkey key, node<Tkey, Tval> *h) {
        if(NULL == h){
            throw KeyNotFoundError();
        }
        if(key == h->key){
            return h->val;
        }
        if(key < h->key){
            return get(key, h->left);
        }
        if(key > h->key){
            return get(key, h->right);
        }
        throw KeyNotFoundError();
    }


    void put(Tkey key, Tval val, node<Tkey, Tval>* &h) {
        if(NULL == h){
            h =  new node<Tkey,Tval>(key,val);
            return;
        }

        if(key == h->key){
            h->val = val;
        }else if(key < h->key){
            put(key, val, h->left);
        }else {
            put(key, val, h->right);
        }
        h->size += 1;
    }

    node<Tkey, Tval>* max(node<Tkey, Tval> *h){
        if(NULL == h){
            return NULL;
        }
        if(NULL == h->right){
            return h;
        }
        
        return max(h->right);
    }

    node<Tkey, Tval>* min(node<Tkey, Tval> *h){
        if(NULL == h){
            return NULL;
        }
        if(NULL == h->left){
            return h;
        }
        
        return min(h->left);

    }
    
  public:
    binary_search_tree() {
        root = NULL;
    }
    ~binary_search_tree()
    {
        delete_tree(root);
    }

    void put(Tkey key, Tval val){
        put(key, val, root);
    }

    Tval get(Tkey key){
        return get(key, root);
    }

    void remove(Tkey key){
        put(key, 0, root, true);
    }

    unsigned size(){
        return root->size;
    }

    Tkey max_key(){
        node<Tkey, Tval> *maxnode = max(root);
        if(NULL == maxnode){
            throw KeyNotFoundError();
        }
        return maxnode->key;
    }
    Tkey min(){
        node<Tkey, Tval> *minnode = min(root);
        if(NULL == minnode){
            throw KeyNotFoundError();
        }
        return minnode->key;
    }

    void debug(node<Tkey, Tval> *h){
        if (NULL == h)return;
        std::cout<<"Key "<<h->key<<" : "<<(h->val)<<std::endl;
        debug(h->left);
        debug(h->right);
    }
    void debug(){
        debug(root);
    }

};

}// namespace binary_search_tree

    

}// namespace data_structure 



}// namespace verihy

#endif

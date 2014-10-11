#ifndef SPLAY_TREE_H 
#define SPLAY_TREE_H 1

#include <algorithm>
#include <exception>
#include <iostream>
#include "../exceptions.hpp"

namespace verihy {

namespace data_structure{

template<typename Tkey, typename Tval>
class splay_tree{
  public:
    class node;
  private:
    // data
    node *root;
    unsigned size;

    // functions
    
    // 0 -- left, 1 -- right
    inline int left_right(node *son){
        node *parent = son->parent;
        return parent->left==son?0:1;
    }
    
    inline node* rotate_right(node *h){
        node *y = h->parent, *b = h->right;
        h->right = y;
        h->parent = y->parent;
        if(0 == left_right(y)){
            y->parent->left = h;
        }else{
            y->parent->right = h;
        }
        y->parent = h;
        b->parent = y;
        y->left = b;
        return h;
    }
    
    inline node* rotate_left(node *h){
        node *y = h->parent, *b = h->left;
        h->left = y;
        h->parent = y->parent;
        if(0 == left_right(y)){
            y->parent->left = h;
        }else{
            y->parent->right = h;
        }
        y->parent = h;
        b->parent = y;
        y->right = b;
        return h;
    }

    void splay(node *h){
        while(h->parent){
            if(root == h->parent){
                if(h->parent->left == h){
                    rotate_right(h);
                }else{
                    rotate_left(h);
                }
            }else if(left_right(h) == left_right(h->parent)){
                if(0 == left_right(h)){
                    rotate_right(h->parent);
                    rotate_right(h);
                }else{
                    rotate_left(h->parent);
                    rotate_left(h);

                }
            }else{
                if(0 == left_right(h)){
                    rotate_right(h);
                    rotate_left(h);
                }else{
                    rotate_left(h);
                    rotate_right(h);
                }
            }
        }
    }

  public:

    class node{
      private:
        node *left, *right, *parent;
        unsigned size;

      public:
        Tkey key;
        Tval val;
        friend class splay_tree;

        node(Tkey key, Tval val, unsigned size=1){
            this->key = key;
            this->val = val;
            this->size = size;
        }
        ~node(){;}
    };// class splay_tree::node

    splay_tree(){
        this->root = NULL;
        this->size = 1;
    }
    ~splay_tree(){
    }

};

// Deprecated
//template<typename Tkey, typename Tval>
//typename splay_tree<Tkey, Tval>::node* splay_tree<Tkey, Tval>::zig(splay_tree<Tkey, Tval>::node *h){
//}


}// namespace data_structure 

}// namespace verihy

#endif // RED_BLACK_TREE_H

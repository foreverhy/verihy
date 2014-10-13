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
        if(y->parent && 0 == left_right(y)){
            y->parent->left = h;
        }
        if(y->parent && 1 == left_right(y)){
            y->parent->right = h;
        }
        y->parent = h;
        y->left = b;
        if(b){
            b->parent = y;
        }
        return h;
    }
    
    inline node* rotate_left(node *h){
        node *y = h->parent, *b = h->left;
        h->left = y;
        h->parent = y->parent;
        if(y->parent && 0 == left_right(y)){
            y->parent->left = h;
        }
        if(y->parent && 1 == left_right(y)){
            y->parent->right = h;
        }
        y->parent = h;
        y->right = b;
        if(b){
            b->parent = y;
        }
        return h;
    }

    void splay(node* h){
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
        this->root = h;
    }// void splay(node *h);

    void debug(node *h){
        using std::cout;
        using std::endl;
        if(NULL == h){
            return;
        }
        cout<<"=========="<<endl;
        //cout<<h->key<<" : "<<h->val<<"  SIZE: "<<h->size<<(h->color==RED?"   [RED]":"   [BLACK]")<<endl;
        cout<<h->key<<" : "<<h->val<<endl;
        cout<<(h->left?h->left->key:' ')<<"<--    -->"<<(h->right?h->right->key:' ')<<endl;
        cout<<"=========="<<endl;

        debug(h->left);
        debug(h->right);

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
            this->left = this->right = this->parent = NULL;
        }
        ~node(){;}
    };// class splay_tree::node

    splay_tree(){
        this->root = NULL;
        this->size = 1;
    }
    ~splay_tree(){
    }
    void put(Tkey key, Tval val){
        if(NULL == root){
            this->root = new node(key, val);
            return;
        }
        node *h = root;
        node *pre = NULL;
        while(h){
           if(key == h->key){
                h->val = val;
                break;
           }else if(key < h->key){
               pre = h;
               h = h->left;
           }else{
               pre = h;
               h = h->right;
           }
        }
        if(NULL == h){
            h = new node(key, val);
            h->parent = pre;
            if(key < pre->key){
                pre->left = h;
            }else{
                pre->right = h;
            }
        }
        splay(h);
    }

    void debug(){
        std::cout<<"****************"<<std::endl;
        debug(root);
        std::cout<<"****************"<<std::endl;
    }

};

// Deprecated
//template<typename Tkey, typename Tval>
//typename splay_tree<Tkey, Tval>::node* splay_tree<Tkey, Tval>::zig(splay_tree<Tkey, Tval>::node *h){
//}


}// namespace data_structure 

}// namespace verihy

#endif // RED_BLACK_TREE_H

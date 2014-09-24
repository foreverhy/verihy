#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H 1

#include <algorithm>
#include <exception>
#include <iostream>
#include "../exceptions.hpp"

namespace verihy {

namespace data_structure{



template<typename Tkey, typename Tval>
class red_black_tree{
  public:
    class node;
  private:

    static const int BLACK = false;
    static const int RED = true;

    node *root;

    inline bool is_red(node *h){
        return NULL==h?false:(RED==h->color);
    }

    inline unsigned size(node *h){
        return NULL==h?0:h->size;
    }

    node* rotate_left(node *h){
        node *x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        x->size = h->size;
        h->size = 1 + size(h->left) + size(h->right);
        return x;
    }

    node* rotate_right(node *h){
        node *x = h->left;
        h->left= x->right;
        x->right= h;
        x->color = h->color;
        h->color = RED;
        x->size = h->size;
        h->size = 1 + size(h->left) + size(h->right);
        return x;
    }

    inline void flip_colors(node *h){
        h->color = RED;
        h->left->color = BLACK;
        h->right->color = BLACK;
    }

    node* get_node(Tkey key, node *h){
        if(NULL == h){
            return NULL;
        }

        if(key == h->key){
            return h;
        }else if(key < h->key){
            return get_node(key, h->left);
        }else{
            return get_node(key, h->right);
        }
    }


    node* put(Tkey key, Tval val, node *h){
        if(NULL == h){
            return  new node(key, val, 1, RED);
        }

        if(key == h->key){
            h->val = val;
        }else if(key < h->key){
            h->left = put(key, val, h->left);
        }else{
            h->right = put(key, val, h->right);
        }

        if(is_red(h->right) && !is_red(h->left)){
            h = rotate_left(h);
        }
        if(is_red(h->left) && is_red(h->left->left)){
            h = rotate_right(h);
        }
        if(is_red(h->right) && is_red(h->left)){
            flip_colors(h);
        }

        h->size = 1 + size(h->left) + size(h->right);
        return h;
    }

    

    void debug(node *h){
        using std::cout;
        using std::endl;
        if(NULL == h){
            return;
        }
        cout<<"=========="<<endl;
        cout<<h->key<<" : "<<h->val<<"  SIZE: "<<h->size<<(h->color==RED?"   [RED]":"   [BLACK]")<<endl;
        cout<<(h->left?h->left->key:' ')<<"<--    -->"<<(h->right?h->right->key:' ')<<endl;
        cout<<"=========="<<endl;

        debug(h->left);
        debug(h->right);

    }


  public:
    class node{
      private:
        node *left, *right;
        int color;// true = red,  false = black;
        unsigned size;

      public:
        Tkey key;
        Tval val;
        friend class red_black_tree;

        node(Tkey key, Tval val, unsigned size , int color){
            this->key = key;
            this->val = val;
            left = right = NULL;
            this->color = color;
            this->size = size;
        }

        ~node(){}
    };
    red_black_tree(){
        this->root = NULL;
    }
    ~red_black_tree(){
        //TODO delete this tree
    }

    Tval get(Tkey key){
        node *h = get_node(key, root);
        if(NULL == h){
            return Tval();
        }
        return h->val;
    }

    node* find(Tkey key){
        return get_node(key, root);
    }

    void put(Tkey key, Tval val){
        this->root = put(key, val, root);
        this->root->color = BLACK;
    }
    void debug(){debug(root);}
};// class red_black_tree



}// namespace data_structure 

}// namespace verihy

#endif // RED_BLACK_TREE_H

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H 1

#include<algorithm>
#include<exception>
#include<iostream>

namespace verihy {

namespace data_structure{

namespace red_black_tree{

const int BLACK = false;
const int RED = true;

template<typename Tkey, typename Tval>
class node{
  public:
    Tkey key;
    Tval val;
    node *left, *right;
    int color;// true = red,  false = black;
    unsigned size;

    node(Tkey key, Tval val, unsigned size , int color){
        this->key = key;
        this->val = val;
        left = right = NULL;
        this->color = color;
        this->size = size;
    }

    ~node(){}
};

template<typename Tkey, typename Tval>
class red_black_tree{
  private:
    node<Tkey, Tval> *root;

    inline bool is_red(node<Tkey, Tval> *h){
        return NULL==h?false:(RED==h->color);
    }

    inline unsigned size(node<Tkey, Tval> *h){
        return NULL==h?0:h->size;
    }

    node<Tkey, Tval>* rotate_left(node<Tkey, Tval> *h){
        node<Tkey, Tval> *x = h->right;
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        x->size = h->size;
        h->size = 1 + size(h->left) + size(h->right);
        return x;
    }

    node<Tkey, Tval>* rotate_right(node<Tkey, Tval> *h){
        node<Tkey, Tval> *x = h->left;
        h->left= x->right;
        x->right= h;
        x->color = h->color;
        h->color = RED;
        x->size = h->size;
        h->size = 1 + size(h->left) + size(h->right);
        return x;
    }

    inline void flip_colors(node<Tkey, Tval> *h){
        h->color = RED;
        h->left->color = BLACK;
        h->right->color = BLACK;
    }

    node<Tkey, Tval>* put(Tkey key, Tval val, node<Tkey, Tval> *h){
        if(NULL == h){
            return  new node<Tkey, Tval>(key, val, 1, RED);
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

    

    void debug(node<Tkey, Tval> *h){
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
    red_black_tree(){
        this->root = NULL;
    }
    ~red_black_tree(){
        //TODO delete this tree
    }

    void put(Tkey key, Tval val){
        this->root = put(key, val, root);
        this->root->color = BLACK;
    }
    void debug(){debug(root);}
};

}// namespace red_black_tree


}// namespace data_structure 

}// namespace verihy

#endif // RED_BLACK_TREE_H

/*
 * Deprecated!
 */
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H 1

#include<algorithm>
#include<exception>
#include<iostream>

namespace verihy {

namespace data_structure{

namespace binary_search_tree {



template<typename Tkey, typename Tval>
class node{
  public:
    Tkey key;
    Tval val;
    node *left, *right, *parent;
    unsigned size;

    node(Tkey key, Tval val){
        this->key = key;
        this->val = val;
        left = right = parent= NULL;
        size = 1;
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

    node<Tkey, Tval>* get_node(Tkey key, node<Tkey, Tval> *h){
        if(NULL == h){
            return NULL;
        }
        if(key == h->key){
            return h;
        }else if(key <= h->key){
            return get_node(key, h->left);
        }else{
            return get_node(key, h->right);
        }
    }

    Tval get(Tkey key, node<Tkey, Tval> *h) {
        node<Tkey, Tval>* tmpnode = get_node(key, h);
        if(NULL == tmpnode){
            throw KeyNotFoundError();
        }
        return tmpnode->val;
    }


    // return value
    // 0 -- node changed
    // 1 -- node added
    int put(Tkey key, Tval val, node<Tkey, Tval>* &h, node<Tkey, Tval> *parent) {
        if(NULL == h){
            h =  new node<Tkey,Tval>(key,val);
            h->parent = parent;
            return 1;
        }

        int flag = 0;

        if(key == h->key){
            h->val = val;
        }else if(key < h->key){
            flag = put(key, val, h->left, h);
        }else {
            flag = put(key, val, h->right, h);
        }
        if(flag){
            h->size += 1;
        }
        return flag;
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

    // return value
    //  the deleted node
    node<Tkey, Tval>* delete_min(node<Tkey, Tval> *h){
        if(NULL == h){
            return NULL;
        }
        if(h->parent)h->parent->size -= 1;

        if(NULL == h->left){
            if(NULL == h->parent){
                this->root = h->right;
                this->root->parent = NULL;
            }else{
                if(h->parent->left == h){
                    h->parent->left = h->right;
                }else{
                    h->parent->right = h->right;
                }
                if(h->right) h->right->parent = h->parent;
            }
            return h;
        }else{
            return delete_min(h->left);
        }
    }

    node<Tkey, Tval>* delete_max(node<Tkey, Tval> *h){
        if(NULL == h){
            return NULL;
        }
        if(h->parent)h->parent->size -= 1;

        if(NULL == h->right){
            if(NULL == h->parent){
                this->root = h->left;
                this->root->parent = NULL;
            }else{
                if(h->parent->left == h){
                    h->parent->left = h->left;
                }else{
                    h->parent->right = h->left;
                }
                if(h->left) h->left->parent = h->parent;
            }
            return h;
        }else{
            return delete_max(h->right);
        }
    }
    

    node<Tkey, Tval>* remove(Tkey key, node<Tkey, Tval> *h){
        if(NULL == h){
            return NULL;
        }
        if(key == h->key){
            if(NULL == h->right){
                return delete_max(h);
            }else if(NULL == h->left){
                return delete_min(h);
            }
            node<Tkey, Tval>* subsnode = delete_min(h->right);
            //delete_min(h->right);
            subsnode->left = h->left;
            subsnode->right = h->right;
            subsnode->parent = h->parent;
            h->left->parent = subsnode;
            h->right->parent = subsnode;

            if(h->parent->left == h){
                h->parent->left = subsnode;
            }else{
                h->parent->right = subsnode;
            }


            return h;
        }else if(key < h->key){
            return remove(key, h->left);
        }else{
            return remove(key, h->right);
        }
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
        put(key, val, root, NULL);
    }

    Tval get(Tkey key){
        return get(key, root);
    }

    int remove(Tkey key){
        node<Tkey, Tval>* tmp = remove(key, root);
        if(tmp){
            delete tmp;
            return 0;
        }
        return 1;
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
    Tkey min_key(){
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
        std::cout<<"============="<<std::endl;
        debug(root);
        std::cout<<"============="<<std::endl;
    }

};

}// namespace binary_search_tree

    

}// namespace data_structure 



}// namespace verihy

#endif // BINARY_SEARCH_TREE_H 

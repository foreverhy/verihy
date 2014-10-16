#include "trie_tree.h"


namespace verihy{

namespace data_structure{

using std::string;
using std::vector;


trie_tree::trie_tree():size(0){
    root = new node(0);
}

void trie_tree::delete_tree(node *h){
    if(!h)return ;
    delete_tree(h->lchd);
    delete_tree(h->right);

    delete h;
}

trie_tree::~trie_tree(){
    delete_tree(root);
}


void trie_tree::insert(const string &str){
    node *h = root->lchd;
    node *pre = root;
    bool is_right = false;
    std::string::const_iterator cur = str.begin();
    while(cur != str.end()){
        if(!h || *cur < h->data){
            node *nn = new node(*cur);
            if(is_right){
                pre->right = nn;
            }else{
                pre->lchd = nn;
            }
            nn->right = h;
            h = nn;
        }

        pre = h;

        if(*cur == h->data){
            ++cur;
            h->counts++;
            if(cur == str.end()){
                h->word_counts++;
                break;
            }
            h = h->lchd;
            is_right = false;
            continue;
        }
        h = h->right;
        is_right = true;
    }
}

int trie_tree::counts(const string &str, bool ex){
    node *h = root->lchd;
    string::const_iterator cur = str.begin();
    while(cur != str.end()){
        if(!h){
            break;
        }
        if(*cur == h->data){
            ++cur;
            if(cur == str.end()){
                if(ex)return h->counts;
                return h->word_counts;
            }
            h = h->lchd;
            continue;
        }
        h = h->right;
    }
    return 0;
}

int trie_tree::counts(const string &str){
    return counts(str, false);
}

int trie_tree::ex_counts(const string &str){
    return counts(str, true);
}

int trie_tree::delete_node(node *pre, bool is_right, node *h){
    if(!h || h->counts )return 1;
    delete_tree(h->lchd);
    if(!pre)return 0;
    if(is_right){
        pre->right = h->right;
    }else{
        pre->lchd = h->right;
    }
    delete h;
    return 0;
}


void trie_tree::remove(const string &str, bool hardmode){
    if(!counts(str)){
        return;
    }
    node *h = root->lchd;
    node *pre = root;
    bool is_right = false;
    string::const_iterator cur = str.begin();

    while(cur != str.end()){
        if(!h){
            break;
        }
        if(*cur == h->data){
            if(!(--h->counts) && hardmode){
                delete_node(pre, is_right, h); 
                return;
            }
            ++cur;
            if(cur == str.end()){
                h->word_counts--;
            }
            pre = h;
            h = h->lchd;
            is_right = false;
            continue;
        }
        pre = h;
        h = h->right;
        is_right = true;
    }
}

//vector<string&>& trie_tree::sumup(node *h){
    //vector<string&> result;
    //if(!h){
        //return result;
    //}
    //for(node *p = h->lchd; p; p = p->right){
        //result = sumup(h->lchd);
    //}

//}
//

void trie_tree::dfs_string(node *h, string word, vector<string> &res){
    if(!h)return ;
    if(h->word_counts){
        res.push_back(word + h->data);
    }
    dfs_string(h->lchd, word+h->data, res);
    dfs_string(h->right, word, res);
}

vector<string> trie_tree::starts_with(
        const string &str
        ){
    node *h = root->lchd;
    string::const_iterator cur = str.begin();
    vector<string> result;
    while(cur != str.end()){
        if(!h) break;

        if(*cur == h->data){
            ++cur;
            if(cur == str.end()){
                break;
            }
            h = h->lchd;
            continue;
        }
        h = h->right;
    }
    if(!h)return result;
    string word = str;
    if(h->word_counts)result.push_back(word);
    dfs_string(h->lchd, word, result);
    return result;

}



}// namespace data_structure

}// namespace verihy


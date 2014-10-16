#ifndef TRIE_TREE_H
#define TRIE_TREE_H 1

#include <algorithm>
#include <exception>
#include <iostream>
#include "../exceptions.hpp"
#include <string>
#include <vector>

namespace verihy {

namespace data_structure{

class trie_tree{
  private:
    struct node{
        char data;
        int counts;
        int word_counts;

        node *lchd, *right;

        node(char data, int counts = 0, int word_counts = 0):data(data), counts(counts),\
            word_counts(word_counts), lchd(NULL), right(NULL){
        }
    };

    node *root;
    std::size_t size;

    int counts(const std::string &s, bool ex);
    
    void delete_tree(node *h);

    int delete_node(node *pre, bool is_right, node *h);

    void dfs_string(node *h, std::string word, std::vector<std::string> &res);


  public:
    trie_tree();
    ~trie_tree();

    // insert a word to trie(count+1 if exitts)
    void insert(const std::string &s);

    // remove a word from trie(if exists)
    //  hardmode: delete the nodes from memory
    //  softmode: just set 0 to counts
    void remove(const std::string &s, bool hardmode = false);

    // whether s is in the trie?(as a word or sentence)
    // return 0 if not exists
    //  otherwise the counts

    int counts(const std::string &s);
    
    int ex_counts(const std::string &s);

    // return a vector contains all words starts with
    //  string s in this trie
    std::vector<std::string> starts_with(const std::string &s);



};




}// namespace data_structure 

}// namespace verihy

#endif // TRIE_TREE_H

#ifndef VERIHY_GRAPH_SEARCH_H
#define VERIHY_GRAPH_SEARCH_H 1
#include <vector>
#include "../graph.h"

namespace verihy{

namespace graph{

class search{
  private:
    const graph &G;
  public:
    search(const graph &g):G(g){}
    bool marked (unsigned u, unsigned v) ;
    unsigned count(unsigned );
};

class path{
  private:
    const graph &G;
    const unsigned src;
    bool *marked;
    unsigned *edge_to;
  public:
    path(const graph &g, unsigned s):G(g),src(s){
        marked = new bool[g.V()]();
        edge_to = new unsigned[g.V()]();
    }
    ~path(){
        delete []marked;
        delete []edge_to;
    }
    bool has_path_to(unsigned v);
    std::vector<unsigned> path_to(unsigned v);
};

class depth_first_path{
  private:
    const graph &G;
    const unsigned src;
    bool *marked;
    unsigned *edge_to;
    
    void dfs(unsigned )const;
  public:
    depth_first_path(const graph &g, unsigned s):G(g),src(s){
        marked = new bool[g.V()]();
        edge_to = new unsigned[g.V()]();
        dfs(s);
    }
    ~depth_first_path(){
        delete []marked;
        delete []edge_to;
    }
    bool has_path_to(unsigned v);
    std::vector<unsigned> path_to(unsigned v);
};

}// namespace graph

}// namespace verihy


#endif

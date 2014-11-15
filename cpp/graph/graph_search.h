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
  protected:
    const graph &G;
    const unsigned src;
    bool *marked;
    unsigned *edge_to;
  public:
    path(const graph &g, unsigned s):G(g),src(s){
        marked = new bool[g.V()]();
        edge_to = new unsigned[g.V()]();
    }
    virtual ~path(){
        delete []marked;
        delete []edge_to;
    }
    bool has_path_to(unsigned v)const;
    std::vector<unsigned> path_to(unsigned v)const;
};

class depth_first_path:public path{
  private:
    void dfs(unsigned )const;

  public:
    depth_first_path(const graph &g, unsigned s):path(g,s) 
    {
        dfs(s);
    }
    ~depth_first_path(){
    }
};//class depth_first_path

class breadth_first_path:public path {
  private:
    void bfs(unsigned)const;
  public:
    breadth_first_path(const graph &g, unsigned s):path(g,s){
        bfs(s);
    }
    ~breadth_first_path(){}
};



}// namespace graph

}// namespace verihy


#endif

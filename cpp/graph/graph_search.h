#ifndef VERIHY_GRAPH_SEARCH_H
#define VERIHY_GRAPH_SEARCH_H 1
#include <vector>
#include <cstring>
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

class CC{
  private:
    const graph &G;
    bool *marked;
    int *id;
    int count;

    void dfs(unsigned u)const;
  public:
    CC(const graph &g):G(g),count(0){
        marked = new bool[G.V()];
        id = new int[G.V()]();
        //std::memset(marked, false, G.V());
        //std::memset(id, 0, G.V());
        for(unsigned s = 0; s < G.V(); ++s){
            if(!marked[s]) {
                dfs(s);
                count++;
            }
        }
    }
    ~CC(){
        delete []marked;
        delete []id;
    }
    bool connected(unsigned u, unsigned v)const;
    int ccs()const;
};// class CC

class cycle{
  private:
    const graph &G;
    bool *marked;
    bool h_cycle;
    
    void dfs(unsigned, unsigned);

  public:
    cycle(const graph &g):G(g),h_cycle(false){
        marked = new bool[G.V()];
        std::memset(marked, false, G.V());
        for(unsigned s = 0; s < G.V(); ++s){
            if(!marked[s]){
                dfs(s, s);
            }
        }
    }
    ~cycle(){
        delete []marked;
    }
    bool has_cycle(){
        return h_cycle;
    }

};


}// namespace graph

}// namespace verihy


#endif

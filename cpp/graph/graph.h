#ifndef VERIHY_GRAPH_GRAPH_H
#define VERIHY_GRAPH_GRAPH_H 1

#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>


namespace verihy{

namespace graph{


class graph{
  private:
    unsigned num_vertex; // number of vertexs
    unsigned num_edge; // number of edges
    struct edge{
        unsigned v; // edge u-v
        std::shared_ptr<edge> next;
        edge(unsigned idx):v(idx){
        }
    };
    class vertex{
      public:
        unsigned index;
        std::shared_ptr<edge> next_edge;
        vertex(unsigned idx):index(idx), next_edge(NULL){ 
        }
        void add(unsigned v);
        bool has_edge(unsigned v)const;
        unsigned degree()const;

    };


    std::vector<std::shared_ptr<vertex> > adj; 

  public:
    graph(unsigned v);
    ~graph();
    unsigned V()const{ return num_vertex; }
    unsigned E()const{ return num_edge; }
    bool has_edge(unsigned u, unsigned v)const;
    void list_adj(unsigned u)const;
    std::vector<unsigned> adj_vertics(unsigned u)const;
    unsigned degree(unsigned u)const;

    void add_edge(unsigned u, unsigned v);
    
    
}; // class graph



} // namespace graph

} // namespace verihy

#endif // BASE_GRAPH_H

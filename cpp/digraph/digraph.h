#ifndef VERIHY_DIGRAPH_DIGRAPH_H
#define VERIHY_DIGRAPH_DIGRAPH_H 1

#include <memory>
#include <iostream>
#include <vector>

namespace verihy{

namespace digraph{

class digraph{
  using sz_t = unsigned;
  using weight_t = int;
  private:
    sz_t num_vertex;
    sz_t num_edge;
    struct edge{
        sz_t v; //edge u->v
        weight_t weight;
        std::shared_ptr<edge> next;
        edge(sz_t idx, weight_t wt = 0):v(idx),weight(wt){

        }
    };

    struct vertex{
        sz_t index;
        std::shared_ptr<edge> next_edge;
        vertex(sz_t idx):index(idx), next_edge(nullptr){

        }

        void add(sz_t v);
        bool has_edge(sz_t v)const;
        sz_t in_degree()const;
        sz_t out_degree()const;
    };

    std::vector<std::shared_ptr<vertex> > adj;

    // disable auto copy constructor & copy operator
    // declare but not defination
    digraph(const digraph&);
    digraph& operator=(const digraph&);
  public:
    digraph(sz_t v):num_vertex(v){
        for(sz_t i = 0; i < v; ++i){
            adj.push_back(std::make_shared<vertex>(i));
        }
    }
    digraph(std::istream &in);
    ~digraph();
    sz_t V()const{
        return num_vertex;
    }
    
    sz_t E()const{
        return num_edge;
    }

    bool has_edge(sz_t u, sz_t v)const;

    void list_adj(sz_t u)const;

    std::vector<sz_t> adj_vertics(sz_t u)const;

    sz_t in_degree(sz_t u)const;

    sz_t out_degree(sz_t u)const;

    void add_edge(sz_t u, sz_t v);

    digraph& reverse();
}; // class digraph

}// namespace digraph

}// namespace verihy

#endif

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


}// namespace graph

}// namespace verihy


#endif

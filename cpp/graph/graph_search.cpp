#include "../graph.h"


namespace verihy{

namespace graph{

bool search::marked(unsigned u, unsigned v){
    if(u >= G.V() || v >= G.V())return false;
    return G.has_edge(u, v);
}

unsigned search::count(unsigned u){
    return G.count(u);
}

}// namespace graph

}// namespace verihy

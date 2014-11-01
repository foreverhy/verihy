#include "base_graph.h"
#include <memory>

namespace verihy{

namespace graph{


graph::graph(unsigned v):num_vertex(v), num_edge(0){
    for(auto i = 0u; i < v; ++i){
        adj.push_back(std::make_shared<vertex>(i));
    }
}

graph::~graph(){

}


bool graph::has_edge(unsigned u, unsigned v){
    if(u >= num_vertex || v >= num_vertex)return false;
    return adj[u]->has_edge(v);
}

bool graph::vertex::has_edge(unsigned v){
    for(auto e = next_edge; e; e = e->next){
        if(e->v == v){
            return true;
        }
    }
    return false;
}

void graph::vertex::add(unsigned v){
    if(has_edge(v))return;
    auto pedge = std::make_shared<edge>(v);
    pedge->next = this->next_edge;
    this->next_edge = pedge;
}

void graph::add_edge(unsigned u, unsigned v){
    if(has_edge(u, v))return;
    adj[u]->add(v);
    adj[v]->add(u);
    ++num_edge;
}

} // namespace graph

} // namespace verihy

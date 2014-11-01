#include "graph.h"
#include <memory>
#include <iostream>

namespace verihy{

namespace graph{


graph::graph(unsigned v):num_vertex(v), num_edge(0){
    for(auto i = 0u; i < v; ++i){
        adj.push_back(std::make_shared<vertex>(i));
    }
}

graph::~graph(){

}


bool graph::has_edge(unsigned u, unsigned v)const{
    if(u >= num_vertex || v >= num_vertex)return false;
    return adj[u]->has_edge(v);
}

bool graph::vertex::has_edge(unsigned v)const{
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

void graph::list_adj(unsigned u)const{
    std::cout<<"Vertex "<<u<<": ";
    for(auto e = adj[u]->next_edge; e; e=e->next){
        std::cout<<e->v<<" ";
    }
    std::cout<<std::endl;
}

std::vector<unsigned> graph::adj_vertics(unsigned u)const{
    std::vector<unsigned> ans;
    for(auto e = adj[u]->next_edge; e; e=e->next){
        ans.push_back(e->v);
    }
    return ans;
}

unsigned graph::vertex::count()const{
    auto ans = 0u;
    for(auto e = next_edge; e; e = e->next){
        ++ans;
    }
    return ans;
}

unsigned graph::count(unsigned u)const{
    return adj[u]->count();
}


} // namespace graph

} // namespace verihy

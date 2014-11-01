#include "../graph.h"

#include <iostream>


int main(){
    using verihy::graph::graph;

    graph G(123);

    std::cout<<G.V()<<std::endl;
    G.add_edge(0, 1);
    G.add_edge(2, 121);
    G.add_edge(2, 1);
    G.add_edge(2, 12);
    G.add_edge(6, 1);
    std::cout<<G.E()<<std::endl;

    G.list_adj(2);
    G.list_adj(1);


    return 0;

}

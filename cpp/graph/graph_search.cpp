#include "../graph.h"


namespace verihy{

namespace graph{

bool search::marked(unsigned u, unsigned v){
    if(u >= G.V() || v >= G.V())return false;
    return G.has_edge(u, v);
}



void depth_first_path::dfs(unsigned u) const{
    marked[u] = true;
    for(auto v: G.adj_vertics(u)){
        if(!marked[v]){
            edge_to[v] = u;
            dfs(v);
        }
    }
}// void depth_first_path::dfs()

bool depth_first_path::has_path_to(unsigned v){
    return marked[v];
}

std::vector<unsigned> depth_first_path::path_to(unsigned v){
    std::vector<unsigned> ans;
    if(!has_path_to(v))return ans;
    for(auto x = v; x != src; x = edge_to[x]){
        ans.push_back(x);
    }
    ans.push_back(src);
    std::reverse(ans.begin(), ans.end());
    return ans;
}


}// namespace graph

}// namespace verihy

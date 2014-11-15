#include "../graph.h"

#include <queue>

namespace verihy{

namespace graph{

bool search::marked(unsigned u, unsigned v){
    if(u >= G.V() || v >= G.V())return false;
    return G.has_edge(u, v);
}

bool path::has_path_to(unsigned v)const {
    return marked[v];
}

std::vector<unsigned> path::path_to(unsigned v)const{
    std::vector<unsigned> ans;
    if(!has_path_to(v))return ans;
    for(auto x = v; x != src; x = edge_to[x]){
        ans.push_back(x);
    }
    ans.push_back(src);
    std::reverse(ans.begin(), ans.end());
    return ans;
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


void breadth_first_path::bfs(unsigned u)const{
    std::queue<unsigned> qv;    
    marked[u] = true;
    qv.push(u);
    while(!qv.empty()){
        unsigned now = qv.front();
        for(auto v : G.adj_vertics(now)){
            if(!marked[v]){
                marked[v] = true;
                qv.push(v);
                edge_to[v] = now;
            }
        }
        qv.pop();
    }
}





}// namespace graph

}// namespace verihy

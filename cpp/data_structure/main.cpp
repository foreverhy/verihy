#include"data_structure.hpp"
#include<iostream>

int main(int argc, char *argv[])
{
    //verihy::priority_queue::priority_queue<int> a(5000050);
    //int x;
    //while(std::cin>>x){
        //a.insert(x);
    //}
    //while(!a.is_empty()){
        //std::cout<<a.pop()<<std::endl;
    //}

    using verihy::data_structure::binary_search_tree::binary_search_tree;
    using verihy::data_structure::binary_search_tree::node;
    binary_search_tree<char,int> a;

    a.put('a', 100);
    a.put('b', 101);
    a.put('c', 102);
    a.put('d', 104);
   // int *b=NULL;
   // b = a.get(1);

    a.debug();
    //std::cout<<(*(a.get(1)))<<std::endl;
   // a.put(1, 201);

    std::cout<<*(a.get('a'))<<std::endl;
    std::cout<<*(a.get('b'))<<std::endl;
 //   std::cout<<*(a.get(3))<<std::endl;
    std::cout<<*(a.get('c'))<<std::endl;
  //  std::cout<<*(a.get(5))<<std::endl;
    return 0;
}

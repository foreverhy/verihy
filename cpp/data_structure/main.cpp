#include "../data_structure.hpp"
#include<iostream>
#include "red_black_tree.hpp"

using std::cin;
using std::cout;
using std::endl;

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

    //using verihy::data_structure::binary_search_tree::binary_search_tree;
    //using verihy::data_structure::binary_search_tree::node;
    //binary_search_tree<char,int> a;

    //a.put('a', 100);
    //a.debug();
    //a.put('b', 101);
    //a.debug();
    //a.put('c', 102);
    //a.debug();
    //a.put('d', 104);
    //a.debug();
    //a.remove('c');
    //a.debug();
    //a.put('c', 333);
    //a.debug();
    //a.remove('d');
    //a.debug();
   //// int *b=NULL;
   //// b = a.get(1);

    ////std::cout<<(*(a.get(1)))<<std::endl;
   //// a.put(1, 201);

    //try{
        //std::cout<<"MIN: "<<a.min_key()<<std::endl;
        //std::cout<<(a.get('a'))<<std::endl;
        //std::cout<<(a.get('b'))<<std::endl;
     ////   std::cout<<*(a.get(3))<<std::endl;
        //std::cout<<(a.get('c'))<<std::endl;
        //std::cout<<(a.get('e'))<<std::endl;
    //}catch(verihy::data_structure::binary_search_tree::KeyNotFoundError e){
        //cout<<"Exception Catched"<<endl;
    //}
  //  std::cout<<*(a.get(5))<<std::endl;
    using verihy::data_structure::red_black_tree::red_black_tree;

    red_black_tree<char, int>a;
    char keys[10]={
        'A',
        'C',
        'E', 
        'H', 
        'L', 
        'M', 
        'P', 
        'R', 
        'S', 
        'X' 
    };
    //a.put('S', 1);
    //a.put('E', 2);
    //a.put('A', 3);
    //a.put('R', 4);
    //a.put('C', 5);
    //a.put('H', 6);
    //a.put('X', 7);
    //a.put('M', 8);
    //a.put('P', 12);
    //a.put('L', 13);
    
    for(int i = 0; i < 10; ++i){
        a.put(keys[i], i);
    }
    a.debug();


    return 0;
}

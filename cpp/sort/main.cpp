#include "sort.hpp"
#include<algorithm>

int main(void)
{
    int a[900000], x, N=0;
    while(std::cin>>x){
        a[N++] = x;
    }
    //for(int i = 0; i < N; ++i){
        //std::cout<<a[i]<<" ";
    //}
    //std::cout<<std::endl;
    //std::cout<<"#######################"<<std::endl;
    verihy::shellsort::sort(a, 0, N);
    //verihy::quicksort::sort<int>(a, 0, N);
    //std::sort(a, a+N);
    //verihy::mergesort::sort<int>(a, 0, N);
    
    for(int i = 0; i < N; ++i){
        std::cout<<a[i]<<std::endl;
    }
    //std::cout<<std::endl;
    return 0;
}

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H 1

#include<algorithm>
#include<exception>
#include<iostream>

namespace verihy {

namespace data_structure{

class KeyNotFoundError:std::exception {
  public:
    KeyNotFoundError(){
        std::cout<<"Error! Key not found!"<<std::endl;
    }
};

    

}// namespace data_structure 



}// namespace verihy

#endif // BINARY_SEARCH_TREE_H 

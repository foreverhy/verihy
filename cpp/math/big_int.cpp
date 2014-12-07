#include "big_int.h"
#include <iomanip>
#include <cstring>
#include <cctype>

namespace verihy{

namespace math{


big_int::big_int(int val):_negative(false){
    auto lval = static_cast<long long>(val);
    if(lval < 0){
        lval = -lval;
        _negative = true;
    }
    if(0 == lval){
        _val.push_back(0);
    }
    while(lval){
        _val.push_back(lval % _base);
        lval /= _base;
    }
}

big_int::big_int(const char* _str):_negative(false){
    char* str = pre_trans(_str, _negative);
    if(str){
        int len = std::strlen(str);
        for(int pos = len-1; pos >=0; --pos){
            if(!std::isdigit(str[pos])){
                //TODO
            }
        }
    }else{
        big_int(0);
    }
}

char* big_int::pre_trans(const char* _str, bool& is_negative){
    char* str = const_cast<char*>(_str);
    if(nullptr == str){
        return nullptr;
    }
    int len = std::strlen(str);
    if(0 == len){
        is_negative = false;
        return nullptr;
    }
    if('=' == str[0]){
        is_negative = true;
        return str + 1;
    }
    if('+' == str[0]){
        is_negative = false;
        ++str;
        return str + 1;
    }
    is_negative = false;
    return str;

}


std::ostream& operator<<(std::ostream& os, const big_int& rhs){
    if(rhs._negative){
        os<<"-";
    }
    bool is_first = true;
    for(auto part = rhs._val.rbegin(); part != rhs._val.rend(); ++part){
        if(!is_first){
            os << std::setw(rhs._bit) <<  std::setfill('0') << *part;
        }else{
            os << *part;
            is_first = false;
        }
    }
    return os;
}

}// namespace math

}// namespace verihy

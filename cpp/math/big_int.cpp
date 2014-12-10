#include "big_int.h"
#include <iomanip>
#include <cstring>
#include <cctype>
#include <iostream>
#include <algorithm>

#define VERIHY_DEBUG false

namespace verihy{
namespace math{


big_int::big_int(int val):_positive(0){
    auto lval = static_cast<long long>(val);
    if(lval > 0){
        _positive = 1;
    }else if(lval < 0){
        lval = -lval;
        _positive = -1;
    }else{
        _val.push_back(0);
        _positive = 0;
    }

    while(lval){
        _val.push_back(lval % _base);
        lval /= _base;
    }
    _fix_pre_zeros();
}

//big_int::big_int(big_int &&rhs)noexcept:_positive(rhs._positive),_val(rhs._val){
//#if VERIHY_DEBUG
    //std::cout << "move constructor of " << std::endl;
//#endif
//}

big_int::big_int(const big_int& rhs):_positive(rhs._positive),_val(rhs._val){
#if VERIHY_DEBUG
    std::cout << "copy constructor of " << rhs << std::endl;
#endif
}

big_int::big_int(const std::string& str):big_int(str.c_str()){
}

big_int::big_int(const char* _str):_positive(0){
#if VERIHY_DEBUG
    std::cout << "char* constructor of " << _str << std::endl;
#endif
    char* str = _pre_trans(_str, _positive);
    std::vector<char> tmp;
    for(char* pstr = str+std::strlen(str)-1; pstr>=str; --pstr){
        char ch = *pstr; 
        if(std::isdigit(ch)){
            tmp.push_back(_ctoi(ch));
        }else{
            _set_zero();
            return ;
        }
    }
    _val = big_int::trans_base<char, int>(tmp, 10, _base);
    _fix_pre_zeros();
}

char* big_int::_pre_trans(const char* _str, int& positive){
    char* str = const_cast<char*>(_str);
    if(nullptr == str){
        return nullptr;
    }
    int len = std::strlen(str);
    if(0 == len){
        positive = 0;
        return nullptr;
    }
    if('-' == str[0]){
        positive = -1;
        return str + 1;
    }
    if('+' == str[0]){
        positive = 1;
        return str + 1;
    }
    positive = 1;
    return str;

}


std::ostream& operator<<(std::ostream& os, const big_int& rhs){
    if(rhs._positive == 0){
        os << "0";
        return os;
    }
    auto out = big_int::trans_base(rhs._val, rhs._base, rhs._visual_base);
    if(rhs._positive < 0){
        os << "-";
    }
    bool is_first = true;
    for(auto part = out.crbegin(); part != out.crend(); ++part){
        if(!is_first){
            os << std::setw(rhs._visual_bit) <<  std::setfill('0') << *part;
        }else{
            os << *part;
            is_first = false;
        }
    }

    return os;
}

big_int& big_int::operator=(const big_int& rhs){
#if VERIHY_DEBUG
    std::cout << "copy-assignment of " << rhs << std::endl;
#endif
    if(&rhs == this){
        return *this;
    }
    _positive = rhs._positive;
    _val = rhs._val;
    return *this;
}

bool big_int::operator<(const big_int& rhs)const{
    // signs
    if(_positive != rhs._positive){
        return _positive < rhs._positive;
    }else if(!_positive){
        return false;
    }
    auto lenl = _val.size(), lenr = rhs._val.size();
    if(lenl != lenr){
        if(_positive > 0){
            return lenl < lenr;
        }else{
            return lenl > lenr;
        }
    }
    for(auto pl = _val.crbegin(), pr = rhs._val.crbegin();
            pl!=_val.crend(); ++pl, ++pr){
        if(_positive > 0){
            if(*pl < *pr){
                return true;
            }
        }else{
            if(*pl > *pr){
                return true;
            }
        }
    
    }
    return false;
}

bool big_int::operator>(const big_int& rhs)const{
    return rhs.operator<(*this);
}

bool big_int::operator==(const big_int& rhs)const{
    if(_positive != rhs._positive){
        return false;
    }
    auto lenl = _val.size(), lenr = rhs._val.size();
    if(lenl != lenr){
        return false;
    }
    for(auto pl = _val.crbegin(), pr = rhs._val.crbegin();
            pl!=_val.crend(); ++pl, ++pr){
        if(*pl != *pr){
            return false;
        }
    }
    return true;
}

big_int::~big_int(){
#if VERIHY_DEBUG
    std::cout << "==== " << *this << " ===" << std::endl;
    std::cout << "destructor called" << std::endl;
#endif
}


// operators

big_int big_int::operator+(const big_int& rhs){
    big_int ans = 0;
    int carry = 0;
    if(_positive == rhs._positive){
        auto pl = _val.crbegin();
        auto pr = rhs._val.crbegin();
        while(pl!=_val.crend() && pr!=rhs._val.crend()){
            int tmp = *pl + *pr + carry;
            if(tmp >= _base){
                carry = 1;
            }
        }
        // regular add
    }else{
        // sub
    }
    return ans;
}





}// namespace math

}// namespace verihy

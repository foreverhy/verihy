#include "big_int.h"
#include <iomanip>
#include <cstring>
#include <cctype>

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

big_int::big_int(const big_int& rhs):_positive(0){
    _positive = rhs._positive;
    _val = rhs._val;
    //for(auto val: rhs._val){
        //_val.push_back(val);
    //}
}

big_int::big_int(const std::string& str):big_int(str.c_str()){
}

big_int::big_int(const char* _str):_positive(0){
    char* str = _pre_trans(_str, _positive);
    bool zero = true;
    if(str){
        char* pstr = str + std::strlen(str) - 1;
        int cnt = 0;
        int tmp = 0;
        while(pstr >= str){
            if(_bit == cnt){
                _val.push_back(tmp);
                if(tmp)zero = false;
                tmp = 0;
                cnt = 0;
            }
            if(std::isdigit(*pstr)){
                tmp += _ctoi(*pstr) * _weight(cnt);
                --pstr;
                ++cnt;
            }else{
                _set_zero();
                return;
            }
        }
        if(cnt){
            _val.push_back(tmp);
            if(tmp)zero = false;
        }
        if(zero){
            _set_zero();
        }
    }else{
        _set_zero();
    }

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
    if(rhs._positive < 0){
        os<<"-";
    }
    bool is_first = true;
    for(auto part = rhs._val.rbegin(); part != rhs._val.rend(); ++part){
        if(!is_first){
            os << std::setw(rhs._bit) <<  std::setfill('0') << *part;
        //}else if(*part || part == rhs._val.rend()-1){
        }else{
            os << *part;
            is_first = false;
        }
    }
    
    return os;
}

big_int& big_int::operator=(const big_int& rhs){
    _positive = rhs._positive;
    _val = rhs._val;
    //for(auto val: rhs._val){
        //_val.push_back(val);
    //}
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


// add operator


}// namespace math

}// namespace verihy
